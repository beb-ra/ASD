#pragma once
#include <cmath>

class Point {
	double _x;
	double _y;

public:
	Point() : _x(0), _y(0) {}
	Point(double x, double y) : _x(x), _y(y) {}

	double get_x() {
		return _x;
	}
	double get_y() {
		return _y;
	}
};

class Point3D : public Point {
	double _z;

public:
	Point3D() : Point(), _z(0) {}
	Point3D(double x, double y, double z) : Point(x, y), _z(z) {}

	double get_z() {
		return _z;
	}
};