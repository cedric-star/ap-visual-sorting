#include "ui.h"


//DrawText(text, box.x+6, box.y+2, box.height-2, c);
void drawSortChooser(int w, int h) {
    DrawText("choose sorting\nalgorithm", 8, 0, w/40, FSTCOLOR);

    Rectangle rec = {0, 0, ((int) w/4), ((int) h/5*3)};
    drawOutline(rec, 4, FSTCOLOR);
}


void drawTextInput(Rectangle rec, AppState* state) {
    
    
    drawInputField(rec, state->numMaxInput, &state->letCount);
}

#define calcRowY(row, rowNum, rec) (rec.y+(rec.height/rowNum*row))
void drawOptChooser(int w, int h, AppState* state) {
    Rectangle options = {0, h/5*3 - 4, w/4, h/5*2 + 4};
    int spaceRight = 8;
    int rows = 6;
    int fontSize = w/50;

    DrawText("choose parameter", spaceRight, calcRowY(0, rows, options), fontSize, FSTCOLOR);

    
    DrawText("List size n:", spaceRight, calcRowY(1, rows, options), fontSize, FSTCOLOR);

    Rectangle nRec = {spaceRight, calcRowY(2, rows, options), options.width-spaceRight*2, options.height/rows*0.6f};
    drawTextInput(nRec, state);

    DrawText("all distinct?:", spaceRight, calcRowY(3, rows, options), fontSize, FSTCOLOR);

    Rectangle btnRec = {spaceRight, calcRowY(4, rows, options), options.width-spaceRight*2, options.height/rows*0.6f};
    char* btnText = (state->allDistinct) ? "yes" : "no";
    drawButton(btnRec, btnText, &state->allDistinct, btnRec.height);


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
    drawButton(btn, "start", &isPressed, (btn.height+(btn.width/2)) / 3);


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
            algo->id = 3; //hier den passenden algorithmus eintragen
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
    drawSortChooser(w, h);
    drawOptChooser(w, h, state);
    drawStartButton(w, h, state);
}



