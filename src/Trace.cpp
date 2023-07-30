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


//----------------------------------------------
void Sphere::set(Point p, float r)
{
	center = p;
	radius = r;
}

//----------------------------------------------
string Sphere::print()
{
	center.print();
	cout << " " << radius;
	return "";
}

//----------------------------------------------
bool Sphere::sphereIntersect(Ray ray, Point &point, Vec3 &normal)
{
	// Define oc vector
	Point p1 = center;
	Point p2 = ray.point;
	Vec3 oc;
	oc.set(p2.px - p1.px, p2.py - p1.py, p2.pz - p1.pz);

	// Calculate quadratic equation 
	float A = ray.dir.dot(ray.dir);
	float B = 2 * oc.dot(ray.dir);
	float C = oc.dot(oc) - radius*radius;
	// cout << "A = " << A << endl;
	// cout << "B = " << B << endl;
	// cout << "C = " << C << endl;

	// Solve quadratic equation for intersection points
	float discriminant = B*B - 4 * A*C;
	// cout << "discriminant = " << discriminant << endl;
	if (discriminant >= 0)
	{
		// Calculate two roots
		float root1 = (-B - sqrt(discriminant)) / 2 * A;
		float root2 = (-B + sqrt(discriminant)) / 2 * A;
		// cout << "root1 = " << root1 << endl;
		// cout << "root2 = " << root2 << endl;
		float solution = 0;

		// No positive roots found
		if ((root1 < 0) && (root2 < 0))
			return false;

		// One positive root
		else if ((root1 < 0) && (root2 >= 0))
			solution = root2;

		// One positive root
		else if ((root2 < 0) && (root1 >= 0))
			solution = root1;

		// Two positive roots
		else if (root1 <= root2)
			solution = root1;

		// Two positive roots
		else if (root2 <= root1)
			solution = root2;

		// Get intersection point
		point = ray.get_sample(solution);

		// Get surface normal
		normal.set(point.px - center.px, point.py - center.py, point.pz - center.pz);
		normal.normalize();
		return true;
	}
	return false;
}


