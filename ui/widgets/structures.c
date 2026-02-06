
#include "../ui.h"

void drawOutline(Rectangle box, int thickness, Color c) {
    //oben
    DrawRectangle(box.x, box.y, box.width, thickness, c);

    //links
    DrawRectangle(box.x, box.y, thickness, box.height, c);
   
    //untent
    DrawRectangle(box.x, box.y + box.height - thickness, box.width, thickness, c);
    
    //rechts
    DrawRectangle(box.x + box.width - thickness, box.y, thickness, box.height, c);
}