#include "Polynom.h"

Polynom::Polynom(std::string name) : _name(name) {
	Monom zero;
	_polynom.push_back(zero);
}
Polynom::Polynom(const Monom& monom) : _name("default") {
	_polynom.push_back(monom);
}
Polynom::Polynom(std::string name, std::string str) : _name(name) {
	_polynom = PolynomParser::parse(str);
}

Polynom& Polynom::operator=(const Polynom& other) {
	if (this == &other) {
		return *this;
	}
	_name = other._name;
	_polynom = other._polynom;
	return *this;
}

/*
Polynom Polynom::operator*(const Polynom& other) const noexcept {
	Polynom res;
	for (auto it1 = _polynom.begin(); it1 != _polynom.end(); it1++) {
		for (auto it2 = other._polynom.begin(); it2 != other._polynom.end(); it2++) {
			res += (*it1) * (*it2);
		}
	}
	return res;
}
*/

List<Monom> PolynomParser::parse(const std::string& str) {
	bool is_sign_at_begin = false;
	for (int i = 0; i < str.size(); i++) {
		if (str[i] == '+' || str[i] == '-') {
			is_sign_at_begin = true;
			break;
		}
		if (std::isdigit(str[i]) || MonomParser::is_value(str[i]))
			break;
	}

	List<Monom> result;
	std::string new_str = is_sign_at_begin ? str : "+" + str;
	for (size_t i = 0; i < new_str.size(); i++) {
		try {
			Monom monom = MonomParser::parse(str, i);
			result.push_back(monom); // надо попа рядку
		}
		catch (const std::exception& e) {
			throw std::invalid_argument("Failed to parse monom: " + std::string(e.what()));
		}
	}
	return result;
}

std::string Polynom::name() {
	return _name;
}
List<Monom> Polynom::monoms() {
	return _polynom;
}
void Polynom::set_name(const std::string& name) {
	_name = name;
}
