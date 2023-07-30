#include <iostream>
#include <cmath>
using namespace std;

#ifndef VEC3_H_
#define VEC3_H_

class Vec3{
    public:
        float vx;
        float vy;
        float vz;

        void set(float x, float y, float z);
        string print();
        void normalize();
        float dot(Vec3 v);
        void mult(float c);
        void add(Vec3 v);
        void sub(Vec3 v);
};

#endif
