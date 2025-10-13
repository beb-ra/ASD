#pragma once

class Point {
	double _x;
	double _y;

public:
	Point() : _x(0), _y(0) {}
	Point(double x, double y) : _x(x), _y(y) {}
	Point(const Point& other);

	const double get_x() const noexcept;
	const double get_y() const noexcept;

	void set_x(double x);
	void set_y(double y);
};
