#pragma once
#include <iostream>
#include <string>
#define VARS_COUNT 3

class Monom {
	double _coeff;
	int _powers[VARS_COUNT];
public:
	Monom(double coeff = 0);
	Monom(double, const int powers[VARS_COUNT]);
	Monom(double, std::initializer_list<int>);
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
	friend Monom operator/(double, const Monom&);

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
	friend std::ostream& operator<<(std::ostream& os, const Monom&);
};

namespace MonomParser {
	Monom parse(const std::string& str, size_t& pos);
	bool is_value(char c);
	void set_power(int powers[], char var, int value);
	double read_coeff(const std::string& str, size_t& i);
	int read_num(const std::string& str, size_t& i);
	bool parse_sign(const std::string& str, size_t& i);
	double parse_coeff(const std::string& str, size_t& i);
	void parse_variables(const std::string& str, size_t& i, int powers[]);
}