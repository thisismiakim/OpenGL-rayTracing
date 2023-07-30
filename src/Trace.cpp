#include "Trace.h"

void Point::set(float x, float y, float z)
{
    px = x;
    py = y;
    pz = z;
}

//----------------------------------------------
string Point::print()
{
	std::cout << "(" << px << "," << py << "," << pz << ")";
	return "";
}

//----------------------------------------------
float Point::dist(Point p)
{
	float dx = px - p.px;
	float dy = py - p.py;
	float dz = pz - p.pz;
	return sqrt(dx*dx + dy*dy + dz*dz);
}

// -----------------------------------------------

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

// ---------------------------------------------

void Ray::set(Point p, Vec3 d)
{
    point = p;
    dir = d;
    dir.normalize();
}

//----------------------------------------------
void Ray::set(Point p1, Point p2)
{
	point = p1;
	dir.set(p2.px - p1.px, p2.py - p1.py, p2.pz - p1.pz);
	dir.normalize();
}

//----------------------------------------------
string Ray::print()
{
	point.print(); cout << " "; dir.print();
	return "";
}

//----------------------------------------------
Point Ray::get_sample(float t)
{
	Point result;
	result.set(point.px + t*dir.vx, point.py + t*dir.vy, point.pz + t*dir.vz);
	return result;
}
