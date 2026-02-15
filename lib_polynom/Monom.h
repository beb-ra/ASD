#pragma once
#include <iostream>
#define VARS_COUNT 3

class Monom {
	double _coeff;
	int _powers[VARS_COUNT];
public:
	Monom(double coeff = 0);
	Monom(double, const int powers[VARS_COUNT]);
	Monom(const Monom& other);
	Monom& operator=(const Monom& other);

	bool operator==(const Monom&) const noexcept;
	bool operator!=(const Monom&) const noexcept;
	bool operator<(const Monom&) const noexcept;
	bool operator>(const Monom&) const noexcept;

	Monom operator+(const Monom&) const;
	Monom operator-(const Monom&) const;
	Monom operator*(const Monom&) const noexcept;
	Monom operator/(const Monom&) const;

	Monom operator-() const noexcept;

	friend Monom operator*(double, const Monom&) noexcept;
	friend Monom operator/(double, const Monom&) noexcept;

	Monom& operator+=(const Monom&);
	Monom& operator-=(const Monom&);
	Monom& operator*=(const Monom&) noexcept;
	Monom& operator/=(const Monom&);

	double coeff() const;
	int power_x() const;
	int power_y() const;
	int power_z() const;

	double calculate(double, double, double) const;

	//friend std::ostream& operator>>(std::ostream&, const Monom&);
	friend std::ostream& operator<<(std::ostream& os, const Monom& monom);
};