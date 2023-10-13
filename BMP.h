#ifndef BMP_H
#define BMP_H
#include <vector>
#include <iostream>
#include <fstream>
#include <cmath>


#pragma pack(push, 1)
struct BMPFileHeader {
    uint16_t file_type{0x4D42};       
    uint32_t file_size{0};            
    uint16_t reserved1{0};            
    uint16_t reserved2{0};            
    uint32_t offset_data{0};          
};

 struct BMPInfoHeader {
    uint32_t size{ 0 };             
    int32_t width{ 0 };                  
    int32_t height{ 0 };             
    uint16_t planes{ 1 };                  
    uint16_t bit_count{ 0 };     
};
#pragma pack(pop)


struct BMP {
    BMP(const char *fname) {
        read(fname);
    }
    void read(const char *fname);
    void write(const char *fname);
    void turn_left();
    void turn_right();
    void gauss(int r);

};

#endif //BMP_H