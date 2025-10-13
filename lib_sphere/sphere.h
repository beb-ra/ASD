#pragma once
#include <cmath>
#include "..\lib_point3d\point3d.h"

enum LocationTypes;

class Sphere {
	Point3D _center;
	double _radius;

public:
	Sphere() : _center(), _radius(0) {}
	Sphere(double x, double y, double z, double radius);
	Sphere(const Point3D& center, double radius);
	Sphere(const Sphere& other);

	const Point3D& get_center() const noexcept;
	const double get_radius() const noexcept;

	void set_center(const Point3D&);
	void set_radius(double);

	double calculate_distance(const Point3D& second) const;

	template <class T> friend LocationTypes figures_comparison(T, T);
};