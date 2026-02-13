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
    drawOutline(titleRec, 4, FSTCOLOR);
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
            int height = calcRowY(shown + 1, rows, algoRec) + gapDiff * 2;

            char accesses[32];
            char repeats[32];
            char time[32];
            int btnDimension = w*h*0.000027f;
            snprintf(accesses, sizeof(accesses), "Accesses: %ld", state->algos[i].accesses);
            snprintf(repeats, sizeof(repeats), "Repeats: %ld", state->algos[i].repeats);
            snprintf(time, sizeof(time), "Time elapsed: %lfs", state->algos[i].time);

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
        char* header = "algorithm,arraylength,alldistinct,sorted,ascending,cputime,accesses,repeats\n";

        FILE *file;
        file = fopen("mydata.txt", "a");
        if (file) fprintf(file, "%s", header);//%s dafür, nicht direkt string reintun

        for (int i = 0; i < state->algoNum; i++) {

            snprintf(line, sizeof(line), "%s,%d,%s,%s,%s,%lf,%ld,%ld\n",
                state->algos[i].name,
                state->algos[i].list->absLength,
                state->allDistinct ? "true" : "false",
                state->allDistinct ? "true" : "false", //muss sorted sein
                state->allDistinct ? "true" : "false",  //muss ascending sein
                state->algos[i].time,
                state->algos[i].accesses,
                state->algos[i].repeats);
            
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



