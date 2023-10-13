#include "BMP.h"
#include <iostream>

int main() {
    // 8 бит файл с шириной кратной 4
    BMP bmp("test1.bmp");
    bmp.write("test1_out.bmp");
    bmp.turn_right();
    bmp.write("test1_right.bmp");
    bmp.turn_left();
    bmp.turn_left();
    bmp.write("test1_left.bmp");
    bmp.gauss(2);
    bmp.write("test1_gauss.bmp");

    //24 бит файл с шириной не кратной 4
    BMP bmp2("test2.bmp");
    bmp2.write("test2_out.bmp");
    bmp2.turn_right();
    bmp2.write("test2_right.bmp");
    bmp2.turn_left();
    bmp2.turn_left();
    bmp2.write("test2_left.bmp");
    bmp2.gauss(5);
    bmp2.write("test2_gauss.bmp");

    //24 бит файл 1920*1280
    BMP bmp3("test3.bmp");
    bmp3.write("test3_out.bmp");
    bmp3.turn_right();
    bmp3.write("test3_right.bmp");
    bmp3.turn_left();
    bmp3.turn_left();
    bmp3.write("test3_left.bmp");
    bmp3.gauss(5);
    bmp3.write("test3_gauss.bmp");

}