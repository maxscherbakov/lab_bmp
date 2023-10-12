#include "BMP.h"
#include <iostream>

int main() {
    // 8 бит файл с шириной кратной 4
    BMP bmp("mind_8.bmp");
    std:: cout << "size mind_8.bmp:" << bmp.file_header.file_size << "\n";
    bmp.write("mind_8_out.bmp");
    bmp.verr_right();
    bmp.write("mind_8_right.bmp");
    bmp.verr_left();
    bmp.verr_left();
    bmp.write("mind_8_left.bmp");
    bmp.gauss(2);
    bmp.write("mind_8_gauss.bmp");

    //24 бит файл с шириной не кратной 4
    BMP bmp2("geom_24.bmp");
    std:: cout << "size geom_24.bmp:" << bmp2.file_header.file_size << "\n";
    bmp2.write("geom_24_out.bmp");
    bmp2.verr_right();
    bmp2.write("geom_24_right.bmp");
    bmp2.verr_left();
    bmp2.verr_left();
    bmp2.write("geom_24_left.bmp");
    bmp2.gauss(5);
    bmp2.write("geom_24_gauss.bmp");

   BMP bmp3("test.bmp");
    std:: cout << "size test.bmp:" << bmp3.file_header.file_size << "\n";
    bmp3.write("test_out.bmp");
    bmp3.verr_right();
    bmp3.write("test_right.bmp");
    bmp3.verr_left();
    bmp3.verr_left();
    bmp3.write("test_left.bmp");
    bmp3.gauss(5);
    bmp3.write("test_gauss.bmp");

}