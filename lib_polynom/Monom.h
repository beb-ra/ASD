#pragma once
#include <iostream>
#define VARS_COUNT 3

class Monom {
	double _coeff;
	int _powers[VARS_COUNT];
public:
	Monom(double coeff = 0);
	Monom(double, const int powers[VARS_COUNT]);

	bool operator==(const Monom&) const noexcept;
	bool operator!=(const Monom&) const noexcept;
	bool operator<(const Monom&) const noexcept;
	bool operator>(const Monom&) const noexcept;

	Monom operator+(const Monom&) const;
	Monom operator-(const Monom&) const;
	Monom operator*(const Monom&) const noexcept;
	Monom operator/(const Monom&) const;

	Monom& operator+=(const Monom&);
	Monom& operator-=(const Monom&);
	Monom& operator*=(const Monom&) noexcept;
	Monom& operator/=(const Monom&);

	double coeff() const;
	int power_x() const;
	int power_y() const;
	int power_z() const;
};