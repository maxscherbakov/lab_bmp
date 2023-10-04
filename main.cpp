#include "BMP.h"
#include <iostream>

int main() {

    BMP bmp("mind_8.bmp");
    std:: cout << bmp.file_header.file_size << "\n";
    bmp.write("out.bmp");
    bmp.verr_right();
    bmp.write("out_right.bmp");
    bmp.verr_left();
    bmp.write("out_right_left.bmp");
    bmp.gauss(5);
    bmp.write("out_gauss_2.bmp");

    BMP bmp2("geom_24.bmp");
    std:: cout << bmp2.file_header.file_size << "\n";
    bmp2.write("out.bmp");
    bmp2.verr_right();
    bmp2.write("out_right.bmp");
    bmp2.verr_left();
    bmp2.write("out_right_left.bmp");
    bmp2.gauss(5);
    bmp2.write("out_gauss.bmp");



}