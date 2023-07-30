#include "Point.h"

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


