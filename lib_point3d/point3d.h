#pragma once
#include "..\lib_point\point.h"

class Point3D : public Point {
	double _z;

public:
	Point3D() : Point(), _z(0) {}
	Point3D(double x, double y, double z) : Point(x, y), _z(z) {}

	double get_z() {
		return _z;
	}
};