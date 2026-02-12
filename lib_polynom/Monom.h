#pragma once
#include <iostream>
#define VARS_COUNT 3

class Monom {
	double _coeff;
	int _powers[VARS_COUNT];
public:
	Monom(double coeff = 0);
	Monom(double, const int powers[VARS_COUNT]);

	bool operator==(const Monom&);
	bool operator!=(const Monom&);
	bool operator<(const Monom&);
	bool operator>(const Monom&);

	/*
	Monom operator+(const Monom&);
	Monom operator-(const Monom&);
	Monom operator*(const Monom&);
	Monom operator/(const Monom&);

	Monom& operator+=(const Monom&);
	Monom& operator-=(const Monom&);
	Monom& operator*=(const Monom&);
	Monom& operator/=(const Monom&); //?
	*/

	double coeff();
	int power_x();
	int power_y();
	int power_z();
};