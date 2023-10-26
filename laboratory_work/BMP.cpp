#include <vector>
#include <iostream>
#include <fstream>
#include <cmath>
#include "BMP.h"


void BMP::gauss(int r) {
    std:: vector <uint8_t> data2(data);
    uint32_t channles = bmp_info_header.bit_count / 8; 
    int padding_now = (4 - channles * bmp_info_header.width % 4) % 4;
    const double PI = 3.141592653589793;
    double e = exp(1);
    std:: vector <double> d(4);
    for (int y = 0; y < bmp_info_header.height; y++){
        for (int x = 0; x < bmp_info_header.width; x++){
            d = {0, 0, 0, 0};
            for (int i = -r; i < r; i++){
                double kf = (1.2/ pow(e, (i*i)/(2*r*r)));
                int ind;
                if (x+i<0 || x+i>=bmp_info_header.width){
                    ind = channles * ((x-i)+y*bmp_info_header.width) + y*padding_now;
                } else {
                    ind = channles * ((x+i)+y*bmp_info_header.width) + y*padding_now;
                }
                for (int pix = 0; pix < channles; pix++) {
                    d[pix] += data[ind+pix] * kf;
                }
            }
            for (int pix = 0; pix < channles; pix++) {
                data2[channles * (x+y*bmp_info_header.width) + y*padding_now+pix] = d[pix]* (1/(2 * PI * r * r));
            }
        }

    }

    for (int y = 0; y < bmp_info_header.height; y++){
        for (int x = 0; x < bmp_info_header.width; x++){
            d = {0, 0, 0, 0};
            for (int i = -r; i < r; i++){
                double kf = (1.2/ pow(e, (i*i)/(2*r*r)));
                int ind;
                if (y+i<0 || y+i>=bmp_info_header.height){
                    ind = channles * (x+(y-i)*bmp_info_header.width) + (y-i)*padding_now;
                } else {
                    ind = channles * (x+(y+i)*bmp_info_header.width) + (y+i)*padding_now;
                }
                for (int pix = 0; pix < channles; pix++) {
                    d[pix] += data2[ind+pix] * kf;
                }
            }
            for (int pix = 0; pix < channles; pix++) {
                data[channles * (x+y*bmp_info_header.width) + y*padding_now+pix] = d[pix];
            }
        }
    }

}

void BMP::read(const char *fname) {
    std:: ifstream inp{fname, std::ios_base::binary};
    if (inp.is_open()) {
        inp.read((char*)&file_header, sizeof(file_header));
        if(file_header.file_type != 0x4D42) throw std::runtime_error("Error! Unrecognized file format.");
        inp.read((char*)&bmp_info_header, sizeof(bmp_info_header));
        uint32_t channels = bmp_info_header.bit_count / 8;
        int padding_now = (4 - channels * bmp_info_header.width % 4) % 4;
        data.resize(bmp_info_header.height * (bmp_info_header.width * bmp_info_header.bit_count / 8 + padding_now));
        header_add.resize(file_header.offset_data - sizeof(file_header) - sizeof(bmp_info_header));
        inp.read((char*)header_add.data(), header_add.size());
        inp.read((char*)data.data(), data.size());
    } else {
        throw std::runtime_error("Unable to open the input image file.");
    }
    inp.close();
}

void BMP::turn_right(){
    std:: vector <uint8_t> data2(data);
    uint32_t channels = bmp_info_header.bit_count / 8;
    int padding_now = (4 - channels * bmp_info_header.width % 4) % 4;
    int padding_next = (4 - channels * bmp_info_header.height % 4) % 4;

    for (uint32_t y = 0; y < bmp_info_header.height; y++){
        for (uint32_t x = 0; x < bmp_info_header.width; x++){
            int32_t ind = channels * ((bmp_info_header.width - x - 1) * bmp_info_header.height + y) + \
            (bmp_info_header.width - x - 1) * padding_next;
            for (int pix = 0; pix < channels; pix++) {
                data[ind+pix] = data2[channels * (x + y * bmp_info_header.width)+pix + y*padding_now];
            }
        }
    }
    std:: swap(bmp_info_header.width, bmp_info_header.height);
}

void BMP::turn_left() {
    std:: vector <uint8_t> data2(data);
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

void BMP::write(const char *fname) {
    std:: ofstream of{fname, std:: ios_base::binary};
    if (of.is_open()) {
        of.write((const char*)&file_header, sizeof(file_header));
        of.write((const char*)&bmp_info_header, sizeof(bmp_info_header));
        of.write((const char*)header_add.data(), header_add.size());
        of.write((const char*)data.data(), data.size());
    }
    of.close();
}

void BMP::size_image(const char *fname) {
    std:: cout << "size " << fname << ":" << file_header.file_size << "\n";
}

