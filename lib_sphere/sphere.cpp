#include <iostream>
#include "sphere.h"

Sphere::Sphere(const double x, const double y,
	const double z, const double radius) : _center(x, y, z) {
	if (radius <= 0) {
		throw std::invalid_argument("the radius cannot be less than 0");
	}
	_radius = radius;
}

Sphere::Sphere(const Sphere& other) {
	if (&other == NULL) {
		throw std::logic_error("The object is empty ");
	}
	_center = other._center;
	_radius = other._radius;
}

Sphere::Sphere(const Point3D& center, const double radius) : _center(center) {
	if (radius <= 0) {
		throw std::invalid_argument("the radius cannot be less than 0");
	}
	_radius = radius;
}

const Point3D& Sphere::get_center() const noexcept {
	return _center;
}

const double Sphere::get_radius() const noexcept {
	return _radius;
}

double Sphere::calculate_distance(const Point3D& second) const {
	int dx = this->_center.get_x() - second.get_x();
	int dy = this->_center.get_y() - second.get_y();
	int dz = this->_center.get_z() - second.get_z();
	return std::sqrt(dx * dx + dy * dy + dz * dz);
}

void Sphere::set_center(const Point3D& center) {
	if (&center == NULL) {
		throw std::logic_error("The object is empty ");
	}
	_center = center;
}

void Sphere::set_radius(const double radius) {
	_radius = radius;
}