#pragma once
#ifndef BMP_READER_H
#define BMP_READER_H
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

struct BMPColorHeader {
    uint32_t red_mask{ 0x00ff0000 };      
    uint32_t green_mask{ 0x0000ff00 };      
    uint32_t blue_mask{ 0x000000ff };       
    uint32_t alpha_mask{ 0xff000000 };     
    uint32_t color_space_type{ 0x73524742 }; 
    uint32_t unused[16]{ 0 };
};

 struct BMPInfoHeader {
    uint32_t size{ 0 };             
    int32_t width{ 0 };                  
    int32_t height{ 0 };             
    uint16_t planes{ 1 };                  
    uint16_t bit_count{ 0 };
    uint32_t compression{ 0 }; 
    uint32_t size_image{ 0 };
    int32_t x_pixels_per_meter{ 0 };
    int32_t y_pixels_per_meter{ 0 };
    uint32_t colors_used{ 0 };             
    uint32_t colors_important{ 0 };        
};
#pragma pack(pop);


struct BMP {
    BMPFileHeader file_header;
    BMPInfoHeader bmp_info_header;
    BMPColorHeader bmp_color_header;
    std::vector<uint8_t> data;
    std::vector<uint8_t> data_rab;

    BMP(const char *fname) {
        read(fname);
    }

    void gauss(int r) {
        std::vector <uint8_t> data2((bmp_info_header.width + r *2 ) * (bmp_info_header.height + r * 2) * bmp_info_header.bit_count / 8);
        uint32_t channles = bmp_info_header.bit_count / 8; 
        int padding_now = (4 - channles * bmp_info_header.width % 4) % 4;
        for (uint y = 0; y < bmp_info_header.height; y++){
            for (uint x = 0; x < bmp_info_header.width; x++){
                for (int pix = 0; pix < channles; pix++) {
                data2[channles * (x+r + (y+r)*(bmp_info_header.width+r*2)) + pix + padding_now * (y+r)] = data[channles * (x + y * bmp_info_header.width) + pix + padding_now*y];
                }
            }
        }
        const double PI = 3.141592653589793;
        double e = exp(1);
        std:: vector <double> d(4);
        for (uint y = 0; y < bmp_info_header.height; y++){
            for (uint x = 0; x < bmp_info_header.width; x++){
                d = {0, 0, 0, 0};
                for (int i = -r; i < r; i++){
                    for (int j = -r; j < r; j++){
                        for (int pix = 0; pix < channles; pix++) {
                            d[pix] += (1.2/ pow(e, (i*i + j*j)/(2*r*r))) * data2[channles * ((x+r + i) + (bmp_info_header.width + r * 2) * (y + r + j)) + pix + (y + r + j)*padding_now];
                        }
                    }
                }
                for (int pix = 0; pix < channles; pix++) {
                    data[channles * (x + y * bmp_info_header.width)+pix+y*padding_now] = d[pix] * (1/(2 * PI * r * r));

                }
            }
        }
    }
    

    void read(const char *fname) {
    	std:: ifstream inp{fname, std::ios_base::binary};
        if (inp) {
            inp.read((char*)&file_header, sizeof(file_header));
            if(file_header.file_type != 0x4D42) throw std::runtime_error("Error! Unrecognized file format.");
            inp.read((char*)&bmp_info_header, sizeof(bmp_info_header));

            if (bmp_info_header.bit_count == 32) {
                if (bmp_info_header.size >= (sizeof(BMPInfoHeader) + sizeof(BMPColorHeader))) {
                    inp.read((char*)&bmp_color_header, sizeof(bmp_color_header));
                }
            }
            data.resize(bmp_info_header.width * bmp_info_header.height * bmp_info_header.bit_count / 8);
            data_rab.resize(file_header.offset_data - sizeof(file_header) - sizeof(bmp_info_header));
            inp.read((char*)data_rab.data(), data_rab.size());
            inp.read((char*)data.data(), data.size());
        } else {
            throw std::runtime_error("Unable to open the input image file.");
        }
        inp.close();
    }

    void verr_right(){
        std::vector <uint8_t> data2(data);
        uint32_t channels = bmp_info_header.bit_count / 8;
        int padding_now = (4 - channels * bmp_info_header.width % 4) % 4;
        int padding_next = (4 - channels * bmp_info_header.height % 4) % 4;

        for (uint32_t y = 0; y < bmp_info_header.height; y++){
            for (uint32_t x = 0; x < bmp_info_header.width; x++){
                int32_t ind = channels * ((bmp_info_header.width - x - 1) * bmp_info_header.height + y) + (bmp_info_header.width - x - 1) * padding_next;
                for (int pix = 0; pix < channels; pix++) {
                    data[ind+pix] = data2[channels * (x + y * bmp_info_header.width)+pix + y*padding_now];
                }
            }
        }
        std:: swap(bmp_info_header.width, bmp_info_header.height);
    }

    void verr_left() {
        std::vector <uint8_t> data2(data);
        uint32_t channels = bmp_info_header.bit_count / 8;
        int padding_now = (4 - channels * bmp_info_header.width % 4) % 4;
        int padding_next = (4 - channels * bmp_info_header.height % 4) % 4;

        for (uint32_t y = 0; y < bmp_info_header.height; y++){
            for (uint32_t x = 0; x < bmp_info_header.width; x++){
                int32_t ind = channels * ((bmp_info_header.height - y - 1) + x * bmp_info_header.height) + x * padding_next;
                for (int pix = 0; pix < channels; pix++) {
                    data[ind+pix] = data2[channels * (x + y *  bmp_info_header.width)+pix+padding_now*y];
                }
            }
        }
        std:: swap(bmp_info_header.width, bmp_info_header.height);
    }

    void write(const char *fname) {
     	std:: ofstream of{fname, std:: ios_base::binary};
        if (of) {
            of.write((const char*)&file_header, sizeof(file_header));
            of.write((const char*)&bmp_info_header, sizeof(bmp_info_header));
            if(bmp_info_header.bit_count == 32) {
                of.write((const char*)&bmp_color_header, sizeof(bmp_color_header));
            }
            of.write((const char*)data_rab.data(), data_rab.size());
            of.write((const char*)data.data(), data.size());
        }
        of.close();
    }
};
#endif