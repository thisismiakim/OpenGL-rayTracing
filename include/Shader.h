#include <iostream>
#include <cmath>
using namespace std;

#ifndef SHADER_H_
#define SHADER_H_


class Phong{
    public:
        // Constructors
        Phong();
        ~Phong();

        // Set methods
        void SetCamera(Point pos);
        void SetLight(RGB color, Vec3 dir);
        void SetObject(RGB color, float ka, float kd, float ks, float kp);

        // Get method
        void GetShade(Point point, Vec3 normal, RGB & color);
    
    private:
        // Camera
        Point CameraPos;

        // Light
        RGB LightColor;
        Vec3 LightDir;

        // Object
        RGB ObjectColor;
        float Ka, Kd, Ks, Kp;
};

#endif