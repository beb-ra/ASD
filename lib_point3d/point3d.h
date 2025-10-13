#pragma once
#include "..\lib_point\point.h"

class Point3D : public Point {
	double _z;

public:
	Point3D() : Point(), _z(0) {}
	Point3D(double x, double y, double z) : Point(x, y), _z(z) {}
	Point3D(const Point& point, double z) : Point(point), _z(z) {}
	Point3D(const Point3D& other);
	
	const double get_z() const noexcept;
	void set_z(double);
};