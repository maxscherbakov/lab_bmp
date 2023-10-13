#ifndef BMP_H
#define BMP_H


struct BMP {
    BMP(const char *fname) {
        read(fname);
    }
    void read(const char *fname);
    void gauss(int r);
    void turn_right();
    void turn_left();
    void write(const char *fname);
    void size_image(const char *fname);
};

#endif //BMP_H