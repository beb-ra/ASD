#include "Monom.h"

Monom::Monom(double coeff) : _coeff(coeff) {
	for (int i = 0; i < VARS_COUNT; i++) {
		_powers[i] = 0;
	}
}

Monom::Monom(double coeff, const int powers[VARS_COUNT]) : _coeff(coeff) {
	for (int i = 0; i < VARS_COUNT; i++) {
		_powers[i] = powers[i];
	}
}

double Monom::coeff() const {
	return _coeff;
}
int Monom::power_x() const {
	return _powers[0];
}
int Monom::power_y() const {
	return _powers[1];
}
int Monom::power_z() const {
	return _powers[2];
}

bool Monom::operator==(const Monom& other) const noexcept {
	for (int i = 0; i < VARS_COUNT; i++) {
		if (_powers[i] != other._powers[i]) {
			return false;
		}
	}
	return true;
}
bool Monom::operator!=(const Monom& other) const noexcept {
	return !((*this) == other);
}
bool Monom::operator>(const Monom& other) const noexcept {
	for (int i = 0; i < VARS_COUNT; i++) {
		if (_powers[i] > other._powers[i]) {
			return true;
		}
		if (_powers[i] < other._powers[i]) {
			return false;
		}
	}
	return false;
}
bool Monom::operator<(const Monom& other) const noexcept {
	for (int i = 0; i < VARS_COUNT; i++) {
		if (_powers[i] < other._powers[i]) {
			return true;
		}
		if (_powers[i] > other._powers[i]) {
			return false;
		}
	}
	return false;
}

Monom Monom::operator+(const Monom& other) const {
	if (*this != other) {
		throw std::invalid_argument("Operations on different monoms aren't available");
	}
	Monom res(*this);
	res += other;
	return res;
}
Monom Monom::operator-(const Monom& other) const {
	if (*this != other) {
		throw std::invalid_argument("Operations on different monoms aren't available");
	}
	Monom res(*this);
	res -= other;
	return res;
}
Monom Monom::operator*(const Monom& other) const noexcept {
	Monom res(*this);
	res *= other;
	return res;
}
Monom Monom::operator/(const Monom& other) const {
	Monom res(*this);
	res /= other;
	return res;
}

Monom& Monom::operator+=(const Monom& other) {
	if (*this != other) {
		throw std::invalid_argument("Operations on different monoms aren't available");
	}
	_coeff += other._coeff;
	return *this;
}
Monom& Monom::operator-=(const Monom& other) {
	if (*this != other) {
		throw std::invalid_argument("Operations on different monoms aren't available");
	}
	_coeff -= other._coeff;
	return *this;
}
Monom& Monom::operator*=(const Monom& other) noexcept {
	_coeff *= other._coeff;
	for (int i = 0; i < VARS_COUNT; i++) {
		_powers[i] += other._powers[i];
	}
	return *this;
}
Monom& Monom::operator/=(const Monom& other) {
	if (other._coeff == 0) {
		throw std::invalid_argument("Can't division by zero");
	}
	_coeff /= other._coeff;
	for (int i = 0; i < VARS_COUNT; i++) {
		_powers[i] -= other._powers[i];
	}
	return *this;
}