#pragma once
#include <cmath>
#include "..\lib_point\point.h"

enum LocationTypes { intersect, touch, inside, not_intersect };

class Circle {
	Point _center;
	double _radius;

public:
	Circle() : _center(), _radius(0) {}
	Circle(double x, double y, double radius) : _center(x, y), _radius(radius) {}  // исключение при отрицательном радиусе
	Point& get_center() {
		return _center;
	}
	double get_radius() {
		return _radius;
	}

	double calculate_distance(Point& second) {
		int dx = this->_center.get_x() - second.get_x();
		int dy = this->_center.get_y() - second.get_y();
		return std::sqrt(dx * dx + dy * dy);
	}

	template <class T> friend LocationTypes figures_comparison(T, T);
};
