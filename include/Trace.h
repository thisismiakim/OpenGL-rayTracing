#include <iostream>
#include <cmath>
using namespace std;

#ifndef TRACE_H_
#define TRACE_H_

class Point{
    public:
        float px;
        float py;
        float pz;

        void set(float x, float y, float z);
        
        string print();
        float dist(Point p);
};

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

class Ray{
    public:
        Point point;
        Vec3 dir;
        void set(Point p, Vec3 d);
        void set(Point p1, Point p2);
        string print();
        Point get_sample(float t);
};

class Sphere
#endif
