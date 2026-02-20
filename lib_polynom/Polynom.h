#pragma once
#include "../lib_list/list.h"
#include "../lib_polynom/Monom.h"

class Polynom {
	List<Monom> _polynom;
	std::string _name;
public:
	Polynom(std::string name = "default");
	Polynom(const Monom& monom); // мб сделать приватным
	Polynom(std::string name, std::string str);

	Polynom& operator=(const Polynom& other);

	Polynom operator+(const Polynom&) const;
	Polynom operator-(const Polynom&) const;
	Polynom operator*(const Polynom&) const noexcept;

	Polynom& operator+=(const Polynom&);
	Polynom& operator-=(const Polynom&);
	Polynom& operator*=(const Polynom&) noexcept;

	Polynom operator-() const noexcept;

	//?
	//friend Polynom operator+(const Monom&, const Polynom&);
	//friend Polynom operator-(const Monom&, const Polynom&);
	//friend Polynom operator*(const Monom&, const Polynom&);

	//friend std::ostream& operator>>(std::ostream&, const Polynom&);
	//friend std::ostream& operator<<(std::ostream& os, const Polynom&);

	std::string name();
	List<Monom>& monoms();
	void set_name(const std::string&);
};

namespace PolynomParser {
	List<Monom> parse(const std::string& str);
	void ordered_insert_monom(List<Monom>& result, const Monom& monom);
}