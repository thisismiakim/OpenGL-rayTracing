#include "RGB.h"

// RGB 색상 설정
void RGB::set(float r, float g, float b)
{
	R = r;
	G = g;
	B = b;
	clamp(); // 색상값 제한 (0-255 범위)
}

//----------------------------------------------
// rgb 색상값 출력
string RGB::print()
{
	std::cout << "(" << int(R) << "," << int(G) << "," << int(B) << ")";
	return "";
}

//----------------------------------------------
// 색상에 스칼라 곱
void RGB::mult(float c)
{
	R *= c;
	G *= c;
	B *= c;
	clamp();
}

// 다른 색상과의
//----------------------------------------------
void RGB::mult(RGB c)
{
	R *= c.R / 255;
	G *= c.G / 255;
	B *= c.B / 255;
	clamp();
}

//----------------------------------------------
void RGB::add(RGB c)
{
	R += c.R;
	G += c.G;
	B += c.B;
	clamp();
}

//----------------------------------------------
void RGB::sub(RGB c)
{
	R -= c.R;
	G -= c.G;
	B -= c.B;
	clamp();
}


// 색상 값 제한 (0-255 범위)
//----------------------------------------------
void RGB::clamp()
{
	if (R < 0) R = 0;
	if (G < 0) G = 0;
	if (B < 0) B = 0;
	if (R > 255) R = 255;
	if (G > 255) G = 255;
	if (B > 255) B = 255;
}

