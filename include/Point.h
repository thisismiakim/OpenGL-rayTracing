#include <iostream>
#include <cmath>
using namespace std;

#ifndef POINT_H_
#define POINT_H_

class Point{
    public:
        float px;
        float py;
        float pz;

        void set(float x, float y, float z);
        string print();
        float dist(Point p);
};

#endif