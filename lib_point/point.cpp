#include <iostream>
#include "point.h"

Point::Point(const Point& other) {
    if (&other == NULL) {
        throw std::logic_error("The object is empty ");
    }
    _x = other._x;
    _y = other._y;
}

const double Point::get_x() const noexcept {
    return _x;
}

const double Point::get_y() const noexcept {
    return _y;
}

void Point::set_x(const double x) {
    _x = x;
}

void Point::set_y(const double y) {
    _y = y;
}