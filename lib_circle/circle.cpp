#include <iostream>
#include "circle.h"

Circle::Circle(const Circle& other) {
    if (&other == NULL) {
        throw std::logic_error("The object is empty ");
    }
    _center = other._center;
    _radius = other._radius;
}

Circle::Circle(double x, double y, double radius) : _center(x, y) {
    if (radius <= 0) {
        throw std::invalid_argument("the radius cannot be less than 0");
    }
    _radius = radius;
}

Circle::Circle(const Point& center, const double radius) : _center(center) {
    if (radius <= 0) {
        throw std::invalid_argument("the radius cannot be less than 0");
    }
    _radius = radius;
}

const Point& Circle::get_center() const noexcept {
    return _center;
}

const double Circle::get_radius() const noexcept {
    return _radius;
}

void Circle::set_center(const Point& center) {
    if (&center == NULL) {
        throw std::logic_error("The object is empty ");
    }
    _center = center;
}

void Circle::set_radius(const double radius) {
    _radius = radius;
}

double Circle::calculate_distance(const Point& second) const {
    int dx = this->_center.get_x() - second.get_x();
    int dy = this->_center.get_y() - second.get_y();
    return std::sqrt(dx * dx + dy * dy);
}