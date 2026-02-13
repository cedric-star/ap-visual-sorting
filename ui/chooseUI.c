#include "ui.h"

void drawSortViewer(int w, int h, AppState* state) {
    Rectangle viewerRec = {w*0.25f - 4, 0, w*0.75f, h};
    int fontSize = w * 0.025f;
    int rows = 4;

    DrawText("View Infos for selected Algorithms", viewerRec.x + spaceRight, calcRowY(0, rows, viewerRec) + 8, fontSize, FSTCOLOR);

    int numPerPage = 3;
    int currentPage = state->showSortViewerPage;
    
    //anzahl angeklickter algos
    int selectedCount = 0;
    for (int i = 0; i < state->algoInfoNum; i++) {
        if (state->algoInfos[i].isSelected) selectedCount++;
    }//muss vor forscheife bestimmt werden für anzahl gesamter seiten
    
    int totalPages = (selectedCount + numPerPage - 1) / numPerPage;
    if (totalPages < 1) totalPages = 1;

    //aktuelle seite begrenzen
    if (currentPage >= totalPages) currentPage = state->showSortViewerPage = totalPages - 1;

    int shown = 0; 
    int selectedIndex = 0;
    
    for (int i = 0; i < state->algoInfoNum; i++) {
        if (!state->algoInfos[i].isSelected) continue;
        
        //indexe, die für die aktuelle seite angezeigt werden
        int pageStart = currentPage * numPerPage;
        int pageEnd = (currentPage + 1) * numPerPage;
        
        if (selectedIndex >= pageStart && selectedIndex < pageEnd) {
            int height = calcRowY(shown + 1, rows, viewerRec) + gapDiff * 2;
            
            DrawText(state->algoInfos[i].name, viewerRec.x + 8, height, fontSize, FSTCOLOR);
            
            int heightOffset = (fontSize * 0.5f);
            int newFontSize = w*h*0.000013f;

            char cases[64];
            snprintf(cases, sizeof(cases), "Best Case: %s, Worst Cases: %s", state->algoInfos[i].bestCase, state->algoInfos[i].worstCase);
            DrawText(cases, viewerRec.x + 8, height + 2.0f * heightOffset, newFontSize, FSTCOLOR);

            char stableness[64];
            snprintf(stableness, sizeof(stableness), "Stability: %s", state->algoInfos[i].stable);
            DrawText(stableness, viewerRec.x + 8, height + 3.0f * heightOffset, newFontSize, FSTCOLOR);

            DrawText(state->algoInfos[i].description, viewerRec.x + 8, height + 4.0f * heightOffset, newFontSize, FSTCOLOR);

            shown++;
        }
        selectedIndex++; 
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

void drawSortChooser(int w, int h, AppState* state) {
    Rectangle sortingRec = {0, 0, w*0.25, h*0.6f};
    int fontSize = w*0.02f;
    int rows = 10;
    
    DrawText("choose sorting\nalgorithm", spaceRight, calcRowY(0, rows, sortingRec)-gapDiff, fontSize, FSTCOLOR);

    //vaiablen für die anzeige auf verschiedenen seiten
    int numPerPage = 7;
    int currentPage = state->showSortChooserPage;  //welche seite aktuell angezeigt werden soll
    int totalPages = (int) ceil((float) state->algoInfoNum / (float) numPerPage);
    if (totalPages < 1) totalPages = 1;

    //jeweilige seite mit verschiedenen algorithmen anzeigen:
    int shown = 0; //eigener zähler in schleife, der hochgeht, wenn tatsächlich eine zeile gezeichnet wurde
    for (int i = 0; i < state->algoInfoNum; i++) {
        int minIndex = state->showSortChooserPage * numPerPage;
        int maxIndex = minIndex + numPerPage;

        if (i >= minIndex && i < maxIndex) {
            int height = calcRowY(shown + 1, rows, sortingRec) + gapDiff * 2;        
            Rectangle btnRec = {w*0.22, height, sortingRec.width*0.07f, sortingRec.width*0.07f};

            char nameAndId[64];
            snprintf(nameAndId, sizeof(nameAndId), "%s %c", state->algoInfos[i].name, state->algoInfos[i].id);
            //DrawText(nameAndId, spaceRight, height, fontSize, FSTCOLOR);
            DrawText(TextFormat("%d: %s", state->algoInfos[i].id, state->algoInfos[i].name), spaceRight, height, fontSize, FSTCOLOR);
            drawButton(btnRec, "", &state->algoInfos[i].isSelected, fontSize, FSTCOLOR);
            shown++;
        }
    }

    //anzeige, welche seite aktuell angezeigt wird
    char pageNumView[32];
    snprintf(pageNumView, sizeof(pageNumView), "Page: %d/%d", currentPage + 1, totalPages);
    DrawText(pageNumView, spaceRight, h*0.55f, fontSize, FSTCOLOR);

    //button, um zur nächsten seite zu gehen
    int btnDimension = w*h*0.000023f;
    Rectangle nextBtnRec = {
        MeasureText(pageNumView, fontSize) + spaceRight + (w*0.06f), 
        h*0.55f, 
        btnDimension,
        btnDimension
    };
    //button, um zur vorherigen seite zu gehen
    Rectangle prevBtnRec = {
        MeasureText(pageNumView, fontSize) + spaceRight + (w*0.01f), 
        h*0.55f, 
        btnDimension,
        btnDimension
    };
    
    //am ende nächste-seite-button wieder auf false setzen und button neu malen
    bool nextPressed = false;
    bool prevPressed = false;
    drawButton(nextBtnRec, ">", &nextPressed, nextBtnRec.height*1.2f, FSTCOLOR);
    if (nextPressed) {
        state->showSortChooserPage++;
        if (state->showSortChooserPage >= totalPages) 
            state->showSortChooserPage = 0;
    }
    drawButton(prevBtnRec, "<", &prevPressed, prevBtnRec.height*1.2f, FSTCOLOR);
    if (prevPressed) {
        state->showSortChooserPage--;
        if (state->showSortChooserPage < 0) 
            state->showSortChooserPage = totalPages-1;
    }
    drawOutline(sortingRec, 4, FSTCOLOR);
}



void drawOptChooser(int w, int h, AppState* state) {
    Rectangle options = {0, h*0.6f - 4, w*0.25f, h*0.4f + 4};
    int rows = 6;
    int fontSize = w*0.02f;

    DrawText("choose\nparameter", spaceRight, calcRowY(0, rows, options)-gapDiff, fontSize, FSTCOLOR);

    
    DrawText("List size n:", spaceRight, calcRowY(1, rows, options), fontSize, FSTCOLOR);
    Rectangle nRec = {spaceRight, calcRowY(2, rows, options)-h*0.02f, options.width-spaceRight*2, options.height/rows*0.6f};
    drawInputField(nRec, state->numMaxInput, &state->letCount, nRec.height-w*0.001f);

    DrawText("all distinct?:", spaceRight, calcRowY(3, rows, options), fontSize, FSTCOLOR);

    Rectangle btnRec = {spaceRight, calcRowY(4, rows, options)-h*0.02f, options.width-spaceRight*2, options.height/rows*0.6f};
    char* btnText = (state->allDistinct) ? "yes" : "no";
    drawButton(btnRec, btnText, &state->allDistinct, btnRec.height-w*0.001f, (Color){0,0,0,0});


    drawOutline(options, 4, FSTCOLOR);
}

void* myThread(void* arg) {
    MyAlgorithm* algo = (MyAlgorithm*) arg;
    initSort(algo);
    //pthread_exit(0);
}

void drawStartButton(int w, int h, AppState* state) {
    int btnX = (int) w / 10 * 8;
    int btnY = (int) h / 20 * 18; 

    int btnWidth = (w / 6); 
    int btnHeight = (h / 14);
    
    
    Rectangle btn = {btnX, btnY, btnWidth, btnHeight};

    bool isPressed = false;
    drawButton(btn, "start", &isPressed, btn.height, FSTCOLOR);


    if (isPressed) {
        state->toDraw = 1;
        state->algoNum = 0;

        int mass = atoi(state->numMaxInput);
        if (mass <= 0 || mass > 1000000) mass = 100;


        int *nums = calloc(mass, sizeof(int));
        if (state->allDistinct){
            setAllDisctinctRanNums(nums, mass); 
        } else {
            setRanNums(nums, mass);
        }

        int counter = 0;
        for (int i = 0; i < state->algoInfoNum; i++) {
            if (state->algoInfos[i].isSelected) {

            
                int *newNums = calloc(mass, sizeof(int));
                memcpy(newNums, nums, mass * sizeof(int));//erstellte liste kopieren

                //listenstrukt allokieren
                List* list = malloc(sizeof(List));
                list->dynLength = mass;
                list->absLength = mass;
                list->nums = newNums; //hier war nums
                list->index = 0;
                list->isFinished = false;

                AlgoInfo info = state->algoInfos[i];
                //algorithmus daten platz allokieren
                MyAlgorithm* algo = malloc(sizeof(MyAlgorithm));
                algo->id = info.id; //hier den passenden algorithmus eintragen
                algo->list = list;
                algo->name = info.name;
                algo->accesses = 0;
                algo->repeats = 0;
                algo->correct = false;
                algo->time = 0;

                //liste und algodaten speichern
                state->algos[counter] = *algo;  //kopie
                state->algos[counter].list = list;  //ointer auf heap

                state->algoNum++;
                int ret = pthread_create(&state->threads[counter], NULL, myThread, &state->algos[counter]);
                printf("thread return: %d, for algo: %s", ret, algo->name);
                counter ++;
            }
        }
    }
}

void drawChooseUI(int w, int h, AppState* state) {
    drawSortChooser(w, h, state);
    drawOptChooser(w, h, state);
    drawSortViewer(w, h, state);
    drawStartButton(w, h, state);
}



