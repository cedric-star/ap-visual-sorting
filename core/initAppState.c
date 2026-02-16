#include "core.h"

void initAlgoInfos(AlgoInfo *algoInfos);

void initAppState(AppState* state) {
    
    //Textfeld mit Nullen füllen
    for (int i = 0; i < 8; i++) {
        state->numMaxInput[i] = '0';
    }
    //Zeige initial im Textfeld "100"
    state->numMaxInput[0] = '1';
    state->numMaxInput[1] = '0';
    state->numMaxInput[2] = '0';
    state->numMaxInput[3] = '\0';
    state->letCount = 0;
    state->toDraw = 0;
    state->allDistinct = false;
    state->sorted = false;
    state->descending = false;
    state->algoNum = 0;
    state->showSortChooserPage = 0;
    state->nextSortChooserPage = false;
    state->showSortViewerPage = 0;
    state->nextSortViewerPage = false;

    int algoInfoNum = MAXARNUM; //maximale Anzahl Algorithmen
    AlgoInfo *algoInfos = calloc(algoInfoNum, sizeof(AlgoInfo));
    initAlgoInfos(algoInfos);

    state->algoInfos = algoInfos;
    state->algoInfoNum = algoInfoNum;

}

//Initialisiert alle Algorithmen-Infos für den Auswahlbildschirm
void initAlgoInfos(AlgoInfo *algoInfos) {
    // Testsort überarbeiten!
    algoInfos[0].id = 0;
    algoInfos[0].name = "TestSort";
    algoInfos[0].description = "Die Liste wird beginnend vom ersten Element (von rechts) angefangen zu sortiert. Jedes Element mit\n"
    "Index i wird mit dem Folgelement mit Index i+1 verglichen. Ist elem(i) > elem(i+1) werden die\n" 
    "Elemente vertauscht. Nach jedem Durchlauf befindet sich das Größte Element der Liste am Ende und\n"
    "die Liste wird anschließend um das derzeit letzte Element verkleinert.";
    algoInfos[0].worstCase = "O(n²)";
    algoInfos[0].averageCase = "O(n²)";
    algoInfos[0].bestCase = "O(n)";
    algoInfos[0].stable = "unknown";
    algoInfos[0].isSelected = false;

    // Bubblesort
    algoInfos[1].id = 1;
    algoInfos[1].name = "Bubblesort";
    algoInfos[1].description = "Die Liste wird beginnend vom ersten Element "
    "(von rechts) angefangen zu sortiert. Jedes Element mit Index i wird mit dem Folgelement "
    "mit Index i+1 verglichen. Ist elem(i) > elem(i+1) werden die Elemente vertauscht. "
    "Nach jedem Durchlauf befindet sich das Größte Element der Liste am Ende und die "
    "Liste wird anschließend um das derzeit letzte Element verkleinert. \n"
    "Link: https://publications.scss.tcd.ie/tech-reports/reports.05/TCD-CS-2005-57.pdf ";
    algoInfos[1].worstCase = "O(n²)";
    algoInfos[1].averageCase = "O(n²)";
    algoInfos[1].bestCase = "O(n)";
    algoInfos[1].stable = "unknown";
    algoInfos[1].isSelected = false;

    // Selectionsort
    algoInfos[2].id = 2;
    algoInfos[2].name = "Selectionsort";
    algoInfos[2].description = "Selection Sort beginnt stets mit dem "
    "ersten Element der Liste. Das Startelement wird als Minimum eingespeichert. "
    "Bei jedem Durchlauf werden alle Elemente der Liste mit dem Minimum verglichen. "
    "Am Ende der Liste angekommen, wird das Minimum am Anfang der Liste platziert und beim "
    "nächsten Durchlauf aus der Liste ausgelassen.\n"
    "Link: https://publications.scss.tcd.ie/tech-reports/reports.05/TCD-CS-2005-57.pdf ";
    algoInfos[2].worstCase = "O(n²)";
    algoInfos[2].averageCase = "O(n²)";
    algoInfos[2].bestCase = "O(n²)";
    algoInfos[2].stable = "unknown";
    algoInfos[2].isSelected = false;

    // Insertionsort
    algoInfos[3].id = 3;
    algoInfos[3].name = "Insertionsort";
    algoInfos[3].description = "Beginnend mit einer Teilliste, die nur das "
    "erste Element der zu sortierenden Liste enthält, wird immer das Element am "
    "Ende der Teilliste in die Teilliste einsortiert. Nach jedem Durchlauf wird die "
    "Teilliste um ein weiteres Element erweitert.\n"
    "Link: https://publications.scss.tcd.ie/tech-reports/reports.05/TCD-CS-2005-57.pdf ";
    algoInfos[3].worstCase = "O(n²)";
    algoInfos[3].averageCase = "O(n²)";
    algoInfos[3].bestCase = "O(n)";
    algoInfos[3].stable = "ja";
    algoInfos[3].isSelected = false;

    // Bogosort
    algoInfos[4].id = 4;
    algoInfos[4].name = "Bogosort";
    algoInfos[4].description = "Bogo Sort ist ein extrem ineffizienter "
    "Sortieralgorithmus, basierend auf dem \"Generier und Teste\"-Paradigma. "
    "Die Liste wird vollständig zufällig angeordnet und danach geprüft, ob sie richtig ist.\n"
    "Link: https://www.geeksforgeeks.org/dsa/bogosort-permutation-sort/ ";
    algoInfos[4].worstCase = "O(?)";
    algoInfos[4].averageCase = "O(n*n!)";
    algoInfos[4].bestCase = "O(n)";
    algoInfos[4].stable = "nein";
    algoInfos[4].isSelected = false;

    // Shellsort
    algoInfos[5].id = 5;
    algoInfos[5].name = "Shellsort";
    algoInfos[5].description = "shellsort fehlt text";
    algoInfos[5].worstCase = "O(n²)";
    algoInfos[5].averageCase = "O(n²)";
    algoInfos[5].bestCase = "O(n²)";
    algoInfos[5].stable = "unknown";
    algoInfos[5].isSelected = false;

    // Heapsort
    algoInfos[6].id = 6;
    algoInfos[6].name = "Heapsort";
    algoInfos[6].description = "Heapsort ist ein vergleichbasierter, in-place Sortieralgorithmus,\n"
    "welcher auf dem Binary Heap basiert. Dies ermöglicht den schnellstmöglichen Zugriff auf \n"
    "das größte Element der originalen Liste. Die Funktionsweise ist mit dem\n"
    "Selectionsort zu vergleichen.";
    algoInfos[6].worstCase = "O(n)";
    algoInfos[6].averageCase = "O(n log n)";
    algoInfos[6].bestCase = "O(n log n)";

    // Bucketsort
    algoInfos[7].id = 7;
    algoInfos[7].name = "Bucketsort";
    algoInfos[7].description = "Alle Elemente der Liste werden in k sogenannte Buckets einsortiert,\n"
    "wobei k die Anzahl der Buckets ist. In einem Bucket befinden sich ähnliche Elemente der Liste.\n"
    "Diese Buckets werden nun sortiert und anschließend zusammengefügt in Sequenz.";
    algoInfos[7].worstCase = "N.A.";
    algoInfos[7].averageCase = "N.A.";
    algoInfos[7].bestCase = "N.A.";
    algoInfos[7].stable = "unknown";
    algoInfos[7].isSelected = false;

   // Quicksort
    algoInfos[8].id = 8;
    algoInfos[8].name = "Quicksort";
    algoInfos[8].description = "Quicksort teilt den Array pro Rekursionsdurchlauf in zwei Arrays, links und rechts\n"
    "eines so genannten pivot-Punktes. Alle Elemente kleiner werden in den linken, und größer in den rechten Array\n"
    "einsortiert. Beim letzten Rekursionsdurchlauf werden dann alle Elemente korekt einsortiert.";
    algoInfos[8].worstCase = "O(n²)";
    algoInfos[8].averageCase = "O(n log n)";
    algoInfos[8].bestCase = "O(n log n)";
    algoInfos[8].stable = "nein";
    algoInfos[8].isSelected = true;

    // Mergesort
    algoInfos[9].id = 9;
    algoInfos[9].name = "Mergesort";
    algoInfos[9].description = "Selection Sort beginnt stets mit dem "
    "ersten Element der Liste. Das Startelement wird als Minimum eingespeichert. "
    "Bei jedem Durchlauf werden alle Elemente der Liste mit dem Minimum verglichen. "
    "Am Ende der Liste angekommen, wird das Minimum am Anfang der Liste platziert und beim "
    "nächsten Durchlauf aus der Liste ausgelassen.\n"
    "Link: https://publications.scss.tcd.ie/tech-reports/reports.05/TCD-CS-2005-57.pdf ";
    algoInfos[9].worstCase = "O(n²)";
    algoInfos[9].averageCase = "O(n²)";
    algoInfos[9].bestCase = "O(n²)";
    algoInfos[9].stable = "unknown";
    algoInfos[9].isSelected = true;

    // Staliensort
    algoInfos[10].id = 10;
    algoInfos[10].name = "Stalinsort";
    algoInfos[10].description = "Selection Sort beginnt stets mit dem "
    "ersten Element der Liste. Das Startelement wird als Minimum eingespeichert. "
    "Bei jedem Durchlauf werden alle Elemente der Liste mit dem Minimum verglichen. "
    "Am Ende der Liste angekommen, wird das Minimum am Anfang der Liste platziert und beim "
    "nächsten Durchlauf aus der Liste ausgelassen.\n"
    "Link: https://publications.scss.tcd.ie/tech-reports/reports.05/TCD-CS-2005-57.pdf ";
    algoInfos[10].worstCase = "O(n²)";
    algoInfos[10].averageCase = "O(n²)";
    algoInfos[10].bestCase = "O(n²)";
    algoInfos[10].stable = "unknown";
    algoInfos[10].isSelected = false;

    //hier fehlt code

        // Selectionsort
    algoInfos[11].id = 11;
    algoInfos[11].name = "Selectionsort";
    algoInfos[11].description = "Selection Sort beginnt stets mit dem "
    "ersten Element der Liste. Das Startelement wird als Minimum eingespeichert. "
    "Bei jedem Durchlauf werden alle Elemente der Liste mit dem Minimum verglichen. "
    "Am Ende der Liste angekommen, wird das Minimum am Anfang der Liste platziert und beim "
    "nächsten Durchlauf aus der Liste ausgelassen.\n"
    "Link: https://publications.scss.tcd.ie/tech-reports/reports.05/TCD-CS-2005-57.pdf ";
    algoInfos[11].worstCase = "O(n²)";
    algoInfos[11].averageCase = "O(n²)";
    algoInfos[11].bestCase = "O(n²)";
    algoInfos[11].stable = "unknown";
    algoInfos[11].isSelected = false;

        // Selectionsort
    algoInfos[12].id = 12;
    algoInfos[12].name = "Selectionsort";
    algoInfos[12].description = "Selection Sort beginnt stets mit dem "
    "ersten Element der Liste. Das Startelement wird als Minimum eingespeichert. "
    "Bei jedem Durchlauf werden alle Elemente der Liste mit dem Minimum verglichen. "
    "Am Ende der Liste angekommen, wird das Minimum am Anfang der Liste platziert und beim "
    "nächsten Durchlauf aus der Liste ausgelassen.\n"
    "Link: https://publications.scss.tcd.ie/tech-reports/reports.05/TCD-CS-2005-57.pdf ";
    algoInfos[12].worstCase = "O(n²)";
    algoInfos[12].averageCase = "O(n²)";
    algoInfos[12].bestCase = "O(n²)";
    algoInfos[12].stable = "unknown";
    algoInfos[12].isSelected = false;

        // Selectionsort
    algoInfos[13].id = 13;
    algoInfos[13].name = "Selectionsort";
    algoInfos[13].description = "Selection Sort beginnt stets mit dem "
    "ersten Element der Liste. Das Startelement wird als Minimum eingespeichert. "
    "Bei jedem Durchlauf werden alle Elemente der Liste mit dem Minimum verglichen. "
    "Am Ende der Liste angekommen, wird das Minimum am Anfang der Liste platziert und beim "
    "nächsten Durchlauf aus der Liste ausgelassen.\n"
    "Link: https://publications.scss.tcd.ie/tech-reports/reports.05/TCD-CS-2005-57.pdf ";
    algoInfos[13].worstCase = "O(n²)";
    algoInfos[13].averageCase = "O(n²)";
    algoInfos[13].bestCase = "O(n²)";
    algoInfos[13].stable = "unknown";
    algoInfos[13].isSelected = false;

    // Bogosort
    algoInfos[14].id = 14;
    algoInfos[14].name = "Bogosort";
    algoInfos[14].description = "Bogo Sort ist ein extrem ineffizienter "
    "Sortieralgorithmus, basierend auf dem \"Generier und Teste\"-Paradigma. "
    "Die Liste wird vollständig zufällig angeordnet und danach geprüft, ob sie richtig ist.\n"
    "Link: https://www.geeksforgeeks.org/dsa/bogosort-permutation-sort/ ";
    algoInfos[14].worstCase = "O(?)";
    algoInfos[14].averageCase = "O(n*n!)";
    algoInfos[14].bestCase = "O(n)";
    algoInfos[14].stable = "nein";
    algoInfos[14].isSelected = false;

     // Selectionsort
    algoInfos[15].id = 15;
    algoInfos[15].name = "Selectionsort";
    algoInfos[15].description = "Selection Sort beginnt stets mit dem "
    "ersten Element der Liste. Das Startelement wird als Minimum eingespeichert. "
    "Bei jedem Durchlauf werden alle Elemente der Liste mit dem Minimum verglichen. "
    "Am Ende der Liste angekommen, wird das Minimum am Anfang der Liste platziert und beim "
    "nächsten Durchlauf aus der Liste ausgelassen.\n"
    "Link: https://publications.scss.tcd.ie/tech-reports/reports.05/TCD-CS-2005-57.pdf ";
    algoInfos[15].worstCase = "O(n²)";
    algoInfos[15].averageCase = "O(n²)";
    algoInfos[15].bestCase = "O(n²)";
    algoInfos[15].stable = "unknown";
    algoInfos[15].isSelected = false;

        // Selectionsort
    algoInfos[16].id = 16;
    algoInfos[16].name = "Selectionsort";
    algoInfos[16].description = "Selection Sort beginnt stets mit dem "
    "ersten Element der Liste. Das Startelement wird als Minimum eingespeichert. "
    "Bei jedem Durchlauf werden alle Elemente der Liste mit dem Minimum verglichen. "
    "Am Ende der Liste angekommen, wird das Minimum am Anfang der Liste platziert und beim "
    "nächsten Durchlauf aus der Liste ausgelassen.\n"
    "Link: https://publications.scss.tcd.ie/tech-reports/reports.05/TCD-CS-2005-57.pdf ";
    algoInfos[16].worstCase = "O(n²)";
    algoInfos[16].averageCase = "O(n²)";
    algoInfos[16].bestCase = "O(n²)";
    algoInfos[16].stable = "unknown";
    algoInfos[16].isSelected = false;

        // Selectionsort
    algoInfos[17].id = 17;
    algoInfos[17].name = "Selectionsort";
    algoInfos[17].description = "Selection Sort beginnt stets mit dem "
    "ersten Element der Liste. Das Startelement wird als Minimum eingespeichert. "
    "Bei jedem Durchlauf werden alle Elemente der Liste mit dem Minimum verglichen. "
    "Am Ende der Liste angekommen, wird das Minimum am Anfang der Liste platziert und beim "
    "nächsten Durchlauf aus der Liste ausgelassen.\n"
    "Link: https://publications.scss.tcd.ie/tech-reports/reports.05/TCD-CS-2005-57.pdf ";
    algoInfos[17].worstCase = "O(n²)";
    algoInfos[17].averageCase = "O(n²)";
    algoInfos[17].bestCase = "O(n²)";
    algoInfos[17].stable = "unknown";
    algoInfos[17].isSelected = false;

        // Selectionsort
    algoInfos[18].id = 18;
    algoInfos[18].name = "Selectionsort";
    algoInfos[18].description = "Selection Sort beginnt stets mit dem "
    "ersten Element der Liste. Das Startelement wird als Minimum eingespeichert. "
    "Bei jedem Durchlauf werden alle Elemente der Liste mit dem Minimum verglichen. "
    "Am Ende der Liste angekommen, wird das Minimum am Anfang der Liste platziert und beim "
    "nächsten Durchlauf aus der Liste ausgelassen.\n"
    "Link: https://publications.scss.tcd.ie/tech-reports/reports.05/TCD-CS-2005-57.pdf ";
    algoInfos[18].worstCase = "O(n²)";
    algoInfos[18].averageCase = "O(n²)";
    algoInfos[18].bestCase = "O(n²)";
    algoInfos[18].stable = "unknown";
    algoInfos[18].isSelected = false;

        // Selectionsort
    algoInfos[19].id = 19;
    algoInfos[19].name = "Selectionsort";
    algoInfos[19].description = "Selection Sort beginnt stets mit dem "
    "ersten Element der Liste. Das Startelement wird als Minimum eingespeichert. "
    "Bei jedem Durchlauf werden alle Elemente der Liste mit dem Minimum verglichen. "
    "Am Ende der Liste angekommen, wird das Minimum am Anfang der Liste platziert und beim "
    "nächsten Durchlauf aus der Liste ausgelassen.\n"
    "Link: https://publications.scss.tcd.ie/tech-reports/reports.05/TCD-CS-2005-57.pdf ";
    algoInfos[19].worstCase = "O(n²)";
    algoInfos[19].averageCase = "O(n²)";
    algoInfos[19].bestCase = "O(n²)";
    algoInfos[19].stable = "unknown";
    algoInfos[19].isSelected = false;

        // Selectionsort
    algoInfos[20].id = 20;
    algoInfos[20].name = "Selectionsort";
    algoInfos[20].description = "Selection Sort beginnt stets mit dem "
    "ersten Element der Liste. Das Startelement wird als Minimum eingespeichert. "
    "Bei jedem Durchlauf werden alle Elemente der Liste mit dem Minimum verglichen. "
    "Am Ende der Liste angekommen, wird das Minimum am Anfang der Liste platziert und beim "
    "nächsten Durchlauf aus der Liste ausgelassen.\n"
    "Link: https://publications.scss.tcd.ie/tech-reports/reports.05/TCD-CS-2005-57.pdf ";
    algoInfos[20].worstCase = "O(n²)";
    algoInfos[20].averageCase = "O(n²)";
    algoInfos[20].bestCase = "O(n²)";
    algoInfos[20].stable = "unknown";
    algoInfos[20].isSelected = false;

        // Selectionsort
    algoInfos[21].id = 21;
    algoInfos[21].name = "Selectionsort";
    algoInfos[21].description = "Selection Sort beginnt stets mit dem "
    "ersten Element der Liste. Das Startelement wird als Minimum eingespeichert. "
    "Bei jedem Durchlauf werden alle Elemente der Liste mit dem Minimum verglichen. "
    "Am Ende der Liste angekommen, wird das Minimum am Anfang der Liste platziert und beim "
    "nächsten Durchlauf aus der Liste ausgelassen.\n"
    "Link: https://publications.scss.tcd.ie/tech-reports/reports.05/TCD-CS-2005-57.pdf ";
    algoInfos[21].worstCase = "O(n²)";
    algoInfos[21].averageCase = "O(n²)";
    algoInfos[21].bestCase = "O(n²)";
    algoInfos[21].stable = "unknown";
    algoInfos[21].isSelected = false;

            // Selectionsort
    algoInfos[22].id = 22;
    algoInfos[22].name = "Selectionsort";
    algoInfos[22].description = "Selection Sort beginnt stets mit dem "
    "ersten Element der Liste. Das Startelement wird als Minimum eingespeichert. "
    "Bei jedem Durchlauf werden alle Elemente der Liste mit dem Minimum verglichen. "
    "Am Ende der Liste angekommen, wird das Minimum am Anfang der Liste platziert und beim "
    "nächsten Durchlauf aus der Liste ausgelassen.\n"
    "Link: https://publications.scss.tcd.ie/tech-reports/reports.05/TCD-CS-2005-57.pdf ";
    algoInfos[22].worstCase = "O(n²)";
    algoInfos[22].averageCase = "O(n²)";
    algoInfos[22].bestCase = "O(n²)";
    algoInfos[22].stable = "unknown";
    algoInfos[22].isSelected = false;

        // Selectionsort
    algoInfos[23].id = 23;
    algoInfos[23].name = "Selectionsort";
    algoInfos[23].description = "Selection Sort beginnt stets mit dem "
    "ersten Element der Liste. Das Startelement wird als Minimum eingespeichert. "
    "Bei jedem Durchlauf werden alle Elemente der Liste mit dem Minimum verglichen. "
    "Am Ende der Liste angekommen, wird das Minimum am Anfang der Liste platziert und beim "
    "nächsten Durchlauf aus der Liste ausgelassen.\n"
    "Link: https://publications.scss.tcd.ie/tech-reports/reports.05/TCD-CS-2005-57.pdf ";
    algoInfos[23].worstCase = "O(n²)";
    algoInfos[23].averageCase = "O(n²)";
    algoInfos[23].bestCase = "O(n²)";
    algoInfos[23].stable = "unknown";
    algoInfos[23].isSelected = false;
        // Selectionsort
    algoInfos[24].id = 24;
    algoInfos[24].name = "Selectionsort";
    algoInfos[24].description = "Selection Sort beginnt stets mit dem "
    "ersten Element der Liste. Das Startelement wird als Minimum eingespeichert. "
    "Bei jedem Durchlauf werden alle Elemente der Liste mit dem Minimum verglichen. "
    "Am Ende der Liste angekommen, wird das Minimum am Anfang der Liste platziert und beim "
    "nächsten Durchlauf aus der Liste ausgelassen.\n"
    "Link: https://publications.scss.tcd.ie/tech-reports/reports.05/TCD-CS-2005-57.pdf ";
    algoInfos[24].worstCase = "O(n²)";
    algoInfos[24].averageCase = "O(n²)";
    algoInfos[24].bestCase = "O(n²)";
    algoInfos[24].stable = "unknown";
    algoInfos[24].isSelected = false;
}
