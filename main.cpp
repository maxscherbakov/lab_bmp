#include "BMP.h"
#include <iostream>

int main() {

    BMP bmp("chel_8.bmp");
    std:: cout << "size mind_8.bmp:" << bmp.file_header.file_size << "\n";
    bmp.write("mind_8_out.bmp");
    bmp.verr_right();
    bmp.write("mind_8_right.bmp");
    bmp.verr_left();
    bmp.write("mind_8_right_left.bmp");
    bmp.gauss(5);
    bmp.write("mind_8_gauss.bmp");

}