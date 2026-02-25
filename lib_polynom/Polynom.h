#pragma once
#include "../lib_list/list.h"
#include "../lib_polynom/monom.h"

class Polynom {
	List<Monom> _polynom;
	std::string _name;
public:
	Polynom(std::string name = "default");
	Polynom(std::string name, const Monom& monom);
	Polynom(std::string name, std::string str);
	Polynom(const Monom& monom);

	Polynom& operator=(const Polynom& other);

	Polynom operator+(const Polynom&) const;
	Polynom operator-(const Polynom&) const;
	Polynom operator*(const Polynom&) const;

	Polynom& operator+=(const Polynom&);
	Polynom& operator-=(const Polynom&);
	Polynom& operator*=(const Polynom&);

	Polynom operator-() const noexcept;

	Polynom operator/(const Monom&) const;
	Polynom& operator/=(const Monom&);

	Polynom& operator+=(double);
	Polynom& operator-=(double);
	Polynom& operator*=(double);
	Polynom& operator/=(double);

	Polynom operator+(double) const;
	Polynom operator-(double) const;
	Polynom operator*(double) const;
	Polynom operator/(double) const;

	friend Polynom operator+(const Monom&, const Polynom&);
	friend Polynom operator-(const Monom&, const Polynom&);
	friend Polynom operator*(const Monom&, const Polynom&);

	friend Polynom operator+(double, const Polynom&);
	friend Polynom operator-(double, const Polynom&);
	friend Polynom operator*(double, const Polynom&);

	friend std::ostream& operator<<(std::ostream&, const Polynom&);
	friend std::istream& operator>>(std::istream& is, Polynom&);

	double calculate(double, double, double) const;

	std::string name() const;
	const List<Monom>& monoms() const;
	List<Monom>& monoms();
	void set_name(const std::string&);
};

namespace PolynomParser {
	List<Monom> parse(const std::string& str);
	void ordered_insert_monom(List<Monom>& result, const Monom& monom);
}