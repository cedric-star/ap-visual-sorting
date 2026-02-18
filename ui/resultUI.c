#include "ui.h"

void drawTitle(int w, int h, AppState* state) {
    Rectangle titleRec = {0, 0, w * 0.4f, h * 0.1f};
    int fontSize = w*0.04f;
    DrawText("Results", spaceRight, 1, fontSize*headerFontMult, FSTCOLOR);
    drawOutline(titleRec, 4, FSTCOLOR);
}

void drawGeneralInfo(int w, int h, AppState* state) {
    Rectangle titleRec = {0, h * 0.1f - 4, w * 0.4f, h * 0.9f + 4};
    int fontSize = w*0.04f;
    int rows = 10;
    drawOutline(titleRec, 4, FSTCOLOR);

    DrawText("General info:", spaceRight, calcRowY(0, rows, titleRec)-gapDiff, fontSize, FSTCOLOR);

    DrawText("List:", spaceRight*2, calcRowY(1, rows, titleRec)-gapDiff, fontSize, FSTCOLOR);

    if(state->algoNum == 0) {
        DrawText("-", spaceRight*3, calcRowY(2, rows, titleRec)-gapDiff, fontSize, FSTCOLOR);
    } else {
        char size[32];  
        snprintf(size, sizeof(size), "%d numbers", state->algos[0].list->dynLength);
        DrawText(size, spaceRight*3, calcRowY(2, rows, titleRec)-gapDiff, fontSize, FSTCOLOR);
    }

    char* txt;
    txt = state->allDistinct ? "All distinct" : "Not all distinct";
    DrawText(txt, spaceRight*3, calcRowY(3, rows, titleRec)-gapDiff, fontSize, FSTCOLOR);
    txt = state->sorted ? "Sorted" : "Unsorted";
    DrawText(txt, spaceRight*3, calcRowY(4, rows, titleRec)-gapDiff, fontSize, FSTCOLOR);

    if(state->sorted) {
        txt = state->descending ? "Descending" : "Ascending";
        DrawText(txt, spaceRight*4, calcRowY(5, rows, titleRec)-gapDiff, fontSize, FSTCOLOR);
    }

}

void drawAlgoInfos(int w, int h, AppState* state) {
    Rectangle algoRec = {0.4f * w - 4, 0, w * 0.6f + 4, h};
    int fontSize = w*0.03f;
    drawOutline(algoRec, 4, FSTCOLOR);

    int rows = 3;
    int numPerPage = 3;
    int currentPage = state->showSortViewerPage;
    
    int totalPages = (state->algoNum + numPerPage - 1) / numPerPage;
    if (totalPages < 1) totalPages = 1;

    int shown = 0; 
    int pageHeight = 0;   
    for (int i = 0; i < state->algoNum; i++) {
        if (pageHeight >= currentPage * numPerPage && shown < (currentPage + 1) * numPerPage) {
            int height = calcRowY(shown + 1, rows, algoRec) - 0.06f * h + gapDiff*1.5;

            char accesses[32];
            char repeats[32];
            char time[32];
            int btnDimension = w*h*0.000027f;
            snprintf(accesses, sizeof(accesses), "Accesses: %ld", state->algos[i].accesses);
            snprintf(repeats, sizeof(repeats), "Repeats: %ld", state->algos[i].repeats);
            snprintf(time, sizeof(time), "CPU-Time elapsed: %lfs", state->algos[i].time);

            DrawText(state->algos[i].name, algoRec.x + 16, height, fontSize, FSTCOLOR);
            DrawText(accesses, algoRec.x + 32, height + fontSize, fontSize, FSTCOLOR);
            DrawText(repeats, algoRec.x + 32, height + fontSize*2, fontSize, FSTCOLOR);
            DrawText(time, algoRec.x + 32, height + fontSize*3, fontSize, FSTCOLOR);
            
            shown++;
        }
        pageHeight++; 
    }

    //anzeige, welche seite aktuell angezeigt wird
    char pageNumView[32];
    int btnDimension = w*h*0.000027f;
    snprintf(pageNumView, sizeof(pageNumView), "Page: %d/%d", currentPage + 1, totalPages);
    DrawText(pageNumView, algoRec.x + 16, h - fontSize - 16, fontSize, FSTCOLOR);
    //button, um zur nächsten seite zu gehen
    Rectangle nextBtnRec = {
        algoRec.x + 16 + MeasureText(pageNumView, fontSize) + (w * 0.08f), 
        h - fontSize - 16, 
        btnDimension,
        btnDimension
    };
    //button, um zur vorherigen seite zu gehen
    Rectangle prevBtnRec = {
        algoRec.x + 16 + MeasureText(pageNumView, fontSize) + 8, 
        h - fontSize - 16,  
        btnDimension,
        btnDimension
    };
    
    //am ende nächste-seite-button wieder auf false setzen und button neu malen
    bool nextPressed = false;
    bool prevPressed = false;
    drawButton(nextBtnRec, ">", &nextPressed, nextBtnRec.height*1.2f, FSTCOLOR);
    if (nextPressed) {
        state->showSortViewerPage++;
        if (state->showSortViewerPage >= totalPages) 
            state->showSortViewerPage = 0;
    }
    drawButton(prevBtnRec, "<", &prevPressed, prevBtnRec.height*1.2f, FSTCOLOR);
    if (prevPressed) {
        state->showSortViewerPage--;
        if (state->showSortViewerPage < 0) 
            state->showSortViewerPage = totalPages-1;
    }

}

void drawExportButton(int w, int h, AppState* state) {

    int btnX = (int) w * 0.85f;
    int btnY = (int) h * 0.92f; 

    int btnWidth = (w * 0.13f); 
    int btnHeight = (h * 0.06f);
    
    
    Rectangle btn = {btnX, btnY, btnWidth, btnHeight};

    bool isPressed = false;
    drawButton(btn, "Export", &isPressed, btn.height, FSTCOLOR);


    if (isPressed) {
        char line[256];
        char* header = "algorithm,arraylength,alldistinct,sorted,ascending,cputime,accesses,repeats,yyyy-mm-dd-hour:minute\n";

        time_t now = time(NULL);
        struct tm *t = localtime(&now);
        char timeStr[64];
        snprintf(timeStr, sizeof(timeStr), "%d-%d-%d-%d:%d",
            t->tm_year + 1900,
            t->tm_mon + 1,
            t->tm_mday,
            t->tm_hour,
            t->tm_min
        );

        
        FILE *file;
        if (access(CSVNAME, F_OK) != 0) {
            file = fopen(CSVNAME, "a");
            fprintf(file, "%s", header);//%s dafür, nicht direkt string reintun        
        } else {
            file = fopen(CSVNAME, "a");
        }
        
        
        for (int i = 0; i < state->algoNum; i++) {

            snprintf(line, sizeof(line), "%s,%d,%s,%s,%s,%lf,%ld,%ld,%s\n",
                state->algos[i].name,
                state->algos[i].list->absLength,
                state->allDistinct ? "true" : "false",
                state->sorted ? "true" : "false",
                state->descending ? "true" : "false", 
                state->algos[i].time,
                state->algos[i].accesses,
                state->algos[i].repeats,
                timeStr
            );
            
            fprintf(file, "%s", line); //%s dafür, nicht direkt string reintun
        }
        fclose(file);
    }
}

void drawResultUI(int w, int h, AppState* state) {
    drawGeneralInfo(w, h, state);
    drawTitle(w, h, state);
    drawAlgoInfos(w, h, state);
    drawExportButton(w, h, state);
}



