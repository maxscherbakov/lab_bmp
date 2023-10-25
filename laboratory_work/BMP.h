#ifndef BMP_H
#define BMP_H

/* Тут внутри должны быть приватные поля, которые у тебя в качестве
 * глобальных переменных в cpp файле. Структуры Хэдеров тоже должны
 * быть тут. */
struct BMP {
    BMP(const char *fname) {
        /* Просто, чтобы ты знал: так делать, когда у тебя есть наследование
         * и виртуальные функции, не надо */
        read(fname);
    }
    void read(const char *fname);
    void gauss(int r);
    void turn_right();
    void turn_left();
    void write(const char *fname);
    void size_image(const char *fname);
    void del_image();
};

#endif //BMP_H