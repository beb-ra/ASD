#include <iostream>
#include "point3d.h"

const double Point3D::get_z() const noexcept {
	return _z;
}

void Point3D::set_z(double z) {
	_z = z;
}

Point3D::Point3D(const Point3D& other) : Point(other) {
    if (&other == NULL) {
        throw std::logic_error("The object is empty ");
    }
    _z = other._z;
}
