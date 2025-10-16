#include <graphics.h>
#include <conio.h>

int main() {
    int gd = DETECT, gm;
    initgraph(&gd, &gm, "");
    circle(250, 200, 50); // center (250,200), radius 50
    getch();
    closegraph();
    return 0;
}