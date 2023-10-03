#include "BMP.h"
#include <iostream>

int main() {

    BMP bmp("mind_8.bmp");
    std:: cout << bmp.file_header.file_size;
    bmp.write("out.bmp");
    bmp.verr_right();
    bmp.write("out_right.bmp");
    bmp.verr_left();
    bmp.write("out_right_left.bmp");
    bmp.gauss_run(1);
    bmp.write("out_gauss.bmp");



}