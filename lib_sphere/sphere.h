#pragma once
#include <cmath>

#include "..\lib_point3d\point3d.h"

class Sphere {
	Point3D _center;
	double _radius;

public:
	Sphere() : _center(), _radius(0) {}
	Sphere(double x, double y, double z, double radius) : _center(x, y, z), _radius(radius) {}
	Point3D& get_center() {
		return _center;
	}
	double get_radius() {
		return _radius;
	}

	double calculate_distance(Point3D& second) {
		int dx = this->_center.get_x() - second.get_x();
		int dy = this->_center.get_y() - second.get_y();
		int dz = this->_center.get_z() - second.get_z();
		return std::sqrt(dx * dx + dy * dy + dz * dz);
	}

	template <class T> friend LocationTypes figures_comparison(T, T);
};