#include "BMP.h"
#include <iostream>

int main() {
    // 8 бит файл с шириной кратной 4
    BMP bmp("mind_8.bmp");
    bmp.write("mind_8_out.bmp");
    bmp.turn_right();
    bmp.write("mind_8_right.bmp");
    bmp.turn_left();
    bmp.turn_left();
    bmp.write("mind_8_left.bmp");
    bmp.gauss(2);
    bmp.write("mind_8_gauss.bmp");

    //24 бит файл с шириной не кратной 4
    BMP bmp2("geom_24.bmp");
    bmp2.write("geom_24_out.bmp");
    bmp2.turn_right();
    bmp2.write("geom_24_right.bmp");
    bmp2.turn_left();
    bmp2.turn_left();
    bmp2.write("geom_24_left.bmp");
    bmp2.gauss(5);
    bmp2.write("geom_24_gauss.bmp");

   BMP bmp3("test.bmp");
    bmp3.write("test_out.bmp");
    bmp3.turn_right();
    bmp3.write("test_right.bmp");
    bmp3.turn_left();
    bmp3.turn_left();
    bmp3.write("test_left.bmp");
    bmp3.gauss(5);
    bmp3.write("test_gauss.bmp");

}