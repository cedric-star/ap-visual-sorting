#include "ui.h"

#define calcRowY(row, rowNum, rec) (rec.y+(rec.height/rowNum*row)+gapDiff)
#define spaceRight 8
#define gapDiff 30
#define headerFontMult 1.6f

/*
oid drawSortViewer(int w, int h, AppState* state) {
    Rectangle viewerRec = {w*0.25f - 4, 0, w*0.75f, h};
    int fontSize = w * 0.025f;
    int rows = 10;

    DrawText("View Infos for selected Algorithms", viewerRec.x + spaceRight, calcRowY(0, rows, viewerRec) + 8, fontSize, FSTCOLOR);

    //vaiablen für die anzeige auf verschiedenen seiten
    int numPerPage = 8;
    int currentPage = state->showSortViewerPage;
    
    // Zähle ausgewählte Items
    int selectedCount = 0;
    for (int i = 0; i < state->algoInfoNum; i++) {
        if (state->algoInfos[i].isSelected) selectedCount++;
    }
    
    int totalPages = (selectedCount + numPerPage - 1) / numPerPage;
    if (totalPages < 1) totalPages = 1;

    int shown = 0; 
    int pageHeight = 0;   
    for (int i = 0; i < state->algoInfoNum; i++) {
        if (!state->algoInfos[i].isSelected) continue;
        
        if (pageHeight >= currentPage * numPerPage && shown < (currentPage + 1) * numPerPage) {
            
            int height = calcRowY(shown + 1, rows, viewerRec) + gapDiff * 2;
            DrawText(state->algoInfos[i].name, viewerRec.x + 8, height, fontSize, FSTCOLOR);
            shown++;
        }
        pageHeight++; 
    }

    //anzeige, welche seite aktuell angezeigt wird
    char pageNumView[32];
    int btnDimension = w*h*0.000027f;
    snprintf(pageNumView, sizeof(pageNumView), "Page: %d/%d", currentPage + 1, totalPages);
    DrawText(pageNumView, viewerRec.x + 8, h - fontSize - 16, fontSize, FSTCOLOR);
    //button, um zur nächsten seite zu gehen
    Rectangle nextBtnRec = {
        viewerRec.x + 8 + MeasureText(pageNumView, fontSize) + (w * 0.08f), 
        h - fontSize - 16, 
        btnDimension,
        btnDimension
    };
    //button, um zur vorherigen seite zu gehen
    Rectangle prevBtnRec = {
        viewerRec.x + 8 + MeasureText(pageNumView, fontSize) + 8, 
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
    drawOutline(viewerRec, 4, FSTCOLOR);
}
*/

void drawTitle(int w, int h, AppState* state) {
    Rectangle titleRec = {0, 0, w * 0.4f, h * 0.1f};
    int fontSize = w*0.04f;
    DrawText("results", spaceRight, 1, fontSize*headerFontMult, FSTCOLOR);
    drawOutline(titleRec, 4, FSTCOLOR);
}

void drawGeneralInfo(int w, int h, AppState* state) {
    Rectangle titleRec = {0, h * 0.1f, w * 0.4f, h * 0.9f};
    int fontSize = w*0.04f;
    drawOutline(titleRec, 4, FSTCOLOR);
}

void drawAlgoInfos(int w, int h, AppState* state) {
    Rectangle titleRec = {0.4f * w, 0, w * 0.6f, h * 0.9f};
    int fontSize = w*0.04f;
    drawOutline(titleRec, 4, FSTCOLOR);
}

void drawExportButton(int w, int h, AppState* state) {

    int btnX = (int) w * 0.85f;
    int btnY = (int) h * 0.92f; 

    int btnWidth = (w * 0.13f); 
    int btnHeight = (h * 0.06f);
    
    
    Rectangle btn = {btnX, btnY, btnWidth, btnHeight};

    bool isPressed = false;
    drawButton(btn, "export", &isPressed, btn.height, FSTCOLOR);


    if (isPressed) {
        //do stuff
    }
}

void drawResultUI(int w, int h, AppState* state) {
    drawGeneralInfo(w, h, state);
    drawTitle(w, h, state);
    drawAlgoInfos(w, h, state);
    drawExportButton(w, h, state);
}



