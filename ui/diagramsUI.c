#include "ui.h"



void drawDiagramsUI(float w, float h, AppState* state) {
    float widthDiv = 1;
    float heightDiv = 1;

    while (widthDiv * heightDiv < state->algoNum) {
        if (widthDiv <= heightDiv) widthDiv++;
        else heightDiv++;
    }

    
    int finishedCounter = 0;
    int counter = 0;
    for (float i = 0; i < widthDiv; i++) {
        for (float j = 0; j < heightDiv; j++) {
            if (counter >= state->algoNum) continue;
            float recW = w / widthDiv;
            float recH = h / heightDiv;
            Rectangle rec = {(recW * i) + 1, (recH * j) + 1, recW - 2, recH - 2};

            char elapsedTime[32];
            snprintf(elapsedTime, sizeof(elapsedTime), "Time elapsed: %lfs", state->algos[counter].time);
            createDiagram(rec, state->algos[counter].list);
            DrawText((state->algos[counter].name), rec.x, rec.y, (w * h * 0.000022f), LIME);
            DrawText(elapsedTime, rec.x, rec.y + (w * h * 0.000022f), (w * h * 0.000022f), LIME);


            if(state->algos[counter].list->isFinished) {finishedCounter++;}
            counter++;
            
            
        }
    }
    if(finishedCounter >= state->algoNum) {state->toDraw = 2;}
}