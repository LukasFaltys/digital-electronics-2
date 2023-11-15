#include <oled.h>

int main(void)
{
    oled_init(OLED_DISP_ON);
    oled_clrscr();





 
 GRAPHICMODE;
oled_drawPixel(3,1,WHITE);
oled_drawPixel(5,1,WHITE);





    // Copy buffer to display RAM
    oled_display();

    while (1) {
        ;
    }

    return 0;
}

