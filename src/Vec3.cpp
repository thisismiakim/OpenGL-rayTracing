#include "Vec3.h"

void Vec3::set(float x, float y, float z)
{
	vx = x;
	vy = y;
	vz = z;
}

//----------------------------------------------
string Vec3::print()
{
	std::cout << "(" << vx << "," << vy << "," << vz << ")";
	return "";
}

//----------------------------------------------
void Vec3::normalize()
{
	float length = sqrt(vx*vx + vy*vy + vz*vz);
	vx /= length;
	vy /= length;
	vz /= length;
}

//----------------------------------------------
float Vec3::dot(Vec3 v)
{
	return vx*v.vx + vy*v.vy + vz*v.vz;
}

//----------------------------------------------
void Vec3::mult(float c)
{
	vx *= c;
	vy *= c;
	vz *= c;
}

//----------------------------------------------
void Vec3::add(Vec3 v)
{
	vx += v.vx;
	vy += v.vy;
	vz += v.vz;
}

//----------------------------------------------
void Vec3::sub(Vec3 v)
{
	vx -= v.vx;
	vy -= v.vy;
	vz -= v.vz;
}