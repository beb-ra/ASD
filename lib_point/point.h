#pragma once

enum LocationTypes { intersect, touch, inside, not_intersect };

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

template <class T>
LocationTypes figures_comparison(T first, T second) {
	double distance = calculate_total_diameter(first, second);
	double radius_sum = first._radius + second._radius;
	double radius_diff = std::abs(static_cast<double>(first._radius) - static_cast<double>(second._radius));

	if (distance > radius_sum) {
		return LocationTypes::not_intersect;
	}
	else if (std::abs(distance - radius_sum) < 1e-10 ||
		std::abs(distance - radius_diff) < 1e-10) {
		return LocationTypes::touch;
	}
	else if (distance <= radius_diff) {
		return LocationTypes::inside;
	}
	else {
		return LocationTypes::intersect;
	}
}

template <class T>
double calculate_total_diameter(T& first, T& second) {
	return first.calculate_distance(second.get_center());
}