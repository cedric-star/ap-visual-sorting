#include "../ui.h"

int findMax(int ar[], int length) {
    int maxValue = 0;
    for(int i = 0; i < length; i++) {
        if (ar[i] > maxValue) {
            maxValue = ar[i];
        }
    }
    return maxValue;
}

void createDiagram(Rectangle box, List* list) {
    int len = list->absLength;
    if (len <= 0) return;
    
    float barWidth = box.width / len;
    int blankPixels = (int) box.width % len;
    
    int maxValue = findMax(list->nums, len);

    
    for(int i = 0; i < len; i++) {
        

        int barHeight = (list->nums[i] * box.height) / maxValue;
        
        int x = box.x + (i * barWidth);
        int y = box.y + box.height - barHeight;
        
        
        if (i == list->index) {
            DrawRectangle(x, y, barWidth+1, barHeight, RED);
        } else {
            DrawRectangle(x, y, barWidth+1, barHeight, LIGHTGRAY);
        }

        if (list->isFinished) {
            DrawRectangle(x, y, barWidth+1, barHeight, GRAY); 
        }

    }
    drawOutline(box, 2, SNDCOLOR);
}