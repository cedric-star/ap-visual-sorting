#include "ui.h"

#define calcRowY(row, rowNum, rec) (rec.y+(rec.height/rowNum*row)+gapDiff)

int spaceRight = 8;
int gapDiff = 30;
int headerFontMult = 1.6f;

void drawSortChooser(int w, int h, AppState* state) {
    Rectangle sortingRec = {0, 0, w*0.25, h*0.6f};
    int fontSize = w*0.02f;
    int rows = 10;
    

    DrawText("choose sorting\nalgorithm", spaceRight, calcRowY(0, rows, sortingRec)-gapDiff, fontSize*headerFontMult, FSTCOLOR);

    //vaiablen für die anzeige auf verschiedenen seiten
    int numPerPage = 3;
    int currentPage = state->showSortChooserPage;  //welche seite aktuell angezeigt werden soll
    int totalPages = (int) ceil((float) state->algoInfoNum / (float) numPerPage);
    if (totalPages < 1) totalPages = 1;

    //jeweilige seite mit verschiedenen algorithmen anzeigen:
    int shown = 0; //eigener zähler in schleife, der hochgeht, wenn tatsächlich eine zeile gezeichnet wurde
    for (int i = 0; i < state->algoInfoNum; i++) {

        int height = calcRowY(shown + 1, rows, sortingRec) + gapDiff * 2;        
        Rectangle btnRec = {w*0.22, height, sortingRec.width*0.07f, sortingRec.width*0.07f};

        int minIndex = state->showSortChooserPage * numPerPage;
        int maxIndex = minIndex + numPerPage;
        if (i >= minIndex && i < maxIndex) {
            DrawText(state->algoInfos[i].name, spaceRight, height, fontSize, FSTCOLOR);
            drawButton(btnRec, "", &state->algoInfos[i].isSelected, fontSize, FSTCOLOR);
            shown++;
        }
    }

    //anzeige, welche seite aktuell angezeigt wird
    char pageNumView[32];
    snprintf(pageNumView, sizeof(pageNumView), "Page: %d/%d", currentPage + 1, totalPages);
    DrawText(pageNumView, spaceRight, h*0.55f, fontSize, FSTCOLOR);

    //button, um zur nächsten seite zu gehen
    Rectangle nextBtnRec = {
        MeasureText(pageNumView, fontSize) + spaceRight + 20, 
        h*0.55f, 
        sortingRec.width*0.09f, 
        sortingRec.width*0.09f
    };
    
    //am ende nächste-seite-button wieder auf false setzen und button neu malen
    bool nextPressed = false;
    drawButton(nextBtnRec, ">", &nextPressed, nextBtnRec.height*2, FSTCOLOR);
    if (nextPressed) {
        state->showSortChooserPage++;
        if (state->showSortChooserPage >= totalPages) 
            state->showSortChooserPage = 0;
    }

    drawOutline(sortingRec, 4, FSTCOLOR);
}



void drawOptChooser(int w, int h, AppState* state) {
    Rectangle options = {0, h*0.6 - 4, w*0.25f, h*0.4f + 4};
    int rows = 6;
    int fontSize = w*0.02f;

    DrawText("choose\nparameter", spaceRight, calcRowY(0, rows, options)-gapDiff, fontSize*headerFontMult, FSTCOLOR);

    
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
        state->algoNum = 1;

        int mass = atoi(state->numMaxInput);
        if (mass <= 0 || mass > 1000000) mass = 100;


        int *nums = calloc(mass, sizeof(int));
        if (state->allDistinct){
            setAllDisctinctRanNums(nums, mass); 
        } else {
            setRanNums(nums, mass);
        }

        for (int i = 0; i < state->algoNum; i++) {
            int *newNums = calloc(mass, sizeof(int));
            memcpy(newNums, nums, mass * sizeof(int));//erstellte liste kopieren

            //listenstrukt allokieren
            List* list = malloc(sizeof(List));
            list->dynLength = mass;
            list->absLength = mass;
            list->nums = nums;
            list->index = 0;
            list->isFinished = false;

            //algorithmus daten platz allokieren
            MyAlgorithm* algo = malloc(sizeof(MyAlgorithm));
            algo->id = 0; //hier den passenden algorithmus eintragen
            algo->list = list;
            algo->name = "Bubblesort";
            algo->accesses = 0;
            algo->repeats = 0;
            algo->correct = false;
            algo->time = 0;

            //liste und algodaten speichern
            state->algos[i] = *algo;  //kopie
            state->algos[i].list = list;  //ointer auf heap

            pthread_create(&state->threads[i], NULL, myThread, algo);
        }
    }
}

void drawChooseUI(int w, int h, AppState* state) {
    drawSortChooser(w, h, state);
    drawOptChooser(w, h, state);
    drawStartButton(w, h, state);
}



