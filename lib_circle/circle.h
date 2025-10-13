#pragma once
#include <cmath>
#include "..\lib_point\point.h"

enum LocationTypes;

class Circle {
	Point _center;
	double _radius;

public:
	Circle() : _center(), _radius(0) {}
	Circle(double x, double y, double radius);
	Circle(const Point& center, double radius);
	Circle(const Circle& other);

	const Point& get_center() const noexcept;
	const double get_radius() const noexcept;

	void set_center(const Point&);
	void set_radius(double);

	double calculate_distance(const Point&) const;

	template <class T> friend LocationTypes figures_comparison(T, T);
};
