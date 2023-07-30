#include <iostream>
#include <cmath>
using namespace std;

#ifndef RGB_H_
#define RGB_H_

class RGB{
    public:
        float R;
        float G;
        float B;

        void set(float r, float g, float b);
        string print();
        void mult(float c);
        void mult(RGB c);
        void add (RGB c);
        void sub(RGB c);
        void clamp();

};


#endif