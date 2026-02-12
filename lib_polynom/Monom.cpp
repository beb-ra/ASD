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

double Monom::coeff() {
	return _coeff;
}
int Monom::power_x() {
	return _powers[0];
}
int Monom::power_y() {
	return _powers[1];
}
int Monom::power_z() {
	return _powers[2];
}

bool Monom::operator==(const Monom&) {

}
bool Monom::operator!=(const Monom&) {

}
bool Monom::operator<(const Monom&) {

}
bool Monom::operator>(const Monom& other) {
	for (int i = 0; i < VARS_COUNT; i++) {
		if (_powers[i] < other._powers[i]) {
			return false;
		}
	}
	return true;
}