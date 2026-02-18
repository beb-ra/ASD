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

Monom::Monom(const Monom& other) : _coeff(other._coeff) {
	for (int i = 0; i < VARS_COUNT; ++i) {
		_powers[i] = other._powers[i];
	}
}

Monom& Monom::operator=(const Monom& other) {
	if (this != &other) {
		_coeff = other._coeff;
		for (int i = 0; i < VARS_COUNT; ++i) {
			_powers[i] = other._powers[i];
		}
	}
	return *this;
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

Monom Monom::operator-() const noexcept {
	Monom res(-_coeff, _powers);
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

Monom operator*(double num, const Monom& monom) noexcept {
	return monom * num;
}
Monom operator/(double num, const Monom& monom) noexcept {
	return monom / num;
}

double Monom::calculate(double x, double y, double z) const {
	return _coeff * pow(x, power_x()) * pow(y, power_y()) * pow(z, power_z());
}

bool MonomParser::is_value(char c) {
	return c == 'x' || c == 'y' || c == 'z';
}

void MonomParser::set_power(int powers[], char var, int value) {
	switch (var) {
	case 'x': powers[0] = value; break;
	case 'y': powers[1] = value; break;
	case 'z': powers[2] = value; break;
	}
}

double MonomParser::read_coeff(const std::string& str, size_t& i) {
	std::string num_str;
	bool has_decimal_point = false;

	while (i < str.size()) {
		if (str[i] == ' ') i++;

		if (std::isdigit(str[i])) {
			num_str += str[i];
			i++;
		}

		else if (str[i] == '.' && !has_decimal_point) {
			num_str += str[i];
			has_decimal_point = true;
			i++;
		}
		else {
			break;
		}
	}

	try {
		double coeff = std::stod(num_str);
		return coeff;
	}
	catch (const std::exception& e) {
		throw std::invalid_argument("Failed to parse coefficient: " + std::string(e.what()));
	}
}

int MonomParser::read_num(const std::string& str, size_t& i) {
	std::string num_str;

	for (; i < str.size(); i++) {
		if (str[i] == ' ') continue;

		if (std::isdigit(str[i])) {
			num_str += str[i];
		}
		else {
			break;
		}
	}
	int num = std::stoi(num_str);
	return num;
}

bool MonomParser::parse_sign(const std::string& str, size_t& i) {
	while (i < str.size()) {
		if (str[i] == ' ') i++;
		if (str[i] == '-') {
			i++;
			return false;
		}
		else if (str[i] == '+') {
			i++;
			return true;
		}
		else {
			throw std::invalid_argument("Uncorrect symbol");
		}
	}
}

double MonomParser::parse_coeff(const std::string& str, size_t& i) {
	double coeff = 1;
	while (i < str.size()) {
		if (str[i] == ' ') i++;

		if (std::isdigit(str[i])) {
			coeff = read_coeff(str, i);
			break;
		}
		else if (is_value(str[i])) break; // coeff = 1
		else {
			throw std::invalid_argument("Uncorrect symbol after operation");
		}
	}
	return coeff;
}

void MonomParser::parse_variables(const std::string& str, size_t& i, int powers[]) {
	while (i < str.size()) {
		while (str[i] == ' ') i++;
		char var;
		if (is_value(str[i])) {
			int pow = 1;
			var = str[i];
			i++;
			while (str[i] == ' ') i++;
			if (str[i] == '^') {
				i++;
				while (str[i] == ' ') i++;
				if (std::isdigit(str[i])) {
					pow = read_num(str, i);
					set_power(powers, var, pow);
					while (str[i] == ' ') i++;
					if (str[i] == '*') i++;
				}
				else {
					throw std::invalid_argument("Uncorrect symbol after ^");
				}
			}
			else if (is_value(str[i])) {
				set_power(powers, var, pow);
				continue;
			}
			else if (str[i] == '*') {
				set_power(powers, var, pow);
				i++;
				continue;
			}
			else {
				throw std::invalid_argument("Uncorrect symbol after variable " + var);
			}
		}
		else {
			return;
		}
	}
}

Monom MonomParser::parse(const std::string& str, size_t& pos) {
	int powers[3] = { 0, 0, 0 };
	size_t i = pos;

	bool is_positive = parse_sign(str, i);
	double coeff = parse_coeff(str, i);

	if (!is_positive) coeff *= -1;
	while (str[i] == ' ') i++;

	if (str[i] == '*') i++;
	else if (str[i] == '+' || str[i] == '-') { // only num in monom
		pos = i;
		Monom res(coeff, powers);
		return res;
	}
	else if (!is_value(str[i]) && i != str.size()) {
		throw std::invalid_argument("Uncorrect symbol");
	}

	parse_variables(str, i, powers);

	pos = i;
	Monom res(coeff, powers);
	return res;
}

std::ostream& operator<<(std::ostream& os, const Monom& monom) {
	if (monom._coeff != 1 && monom._coeff != -1) {
		os << monom._coeff;
	}
	char chars[VARS_COUNT] = { 'x', 'y', 'z' };
	for (int i = 0; i < VARS_COUNT; i++) {
		if (monom._powers[i] != 0) {
			os << chars[i] << "^";
			if (monom._powers[i] > 0 && monom._powers[i] != 1) {
				os << monom._powers[i];
			}
			else if (monom._powers[i] < 0 && monom._powers[i] != -1) {
				os << "(" << monom._powers[i] << ")";
			}
		}
	}
	return os;
}

/*
std::ostream& operator>>(std::ostream& os, const Monom& monom) {
	std::string str;
	os >> str;
	// не парсер а просто обработка наверн
}
*/