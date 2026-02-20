#include "Polynom.h"

Polynom::Polynom(std::string name) : _name(name) {
	//Monom zero;
	//_polynom.push_back(zero);
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

Polynom Polynom::operator+(const Polynom& other) const {
	Polynom res(*this);
	res += other;
	return res;
}

Polynom Polynom::operator-(const Polynom& other) const {
	Polynom res(*this);
	res -= other;
	return res;
}

Polynom Polynom::operator*(const Polynom& other) const noexcept {
	Polynom res;
	for (auto it1 = _polynom.begin(); it1 != _polynom.end(); it1++) {
		for (auto it2 = other._polynom.begin(); it2 != other._polynom.end(); it2++) {
			res += (*it1) * (*it2);
		}
	}
	return res;
}

Polynom& Polynom::operator*=(const Polynom& other) noexcept {
	Polynom res;
	for (auto it1 = _polynom.begin(); it1 != _polynom.end(); it1++) {
		for (auto it2 = other._polynom.begin(); it2 != other._polynom.end(); it2++) {
			res += (*it1) * (*it2);
		}
	}

	_polynom = res._polynom;
	//_polynom = std::move(res._polynom);
	return *this;
}

Polynom& Polynom::operator+=(const Polynom& other) {
	List<Monom> result;
	auto it1 = _polynom.begin();
	auto it2 = other._polynom.begin();

	while (it1 != _polynom.end() && it2 != other._polynom.end()) {
		if (*it1 == *it2) {
			Monom sum = *it1 + *it2;
			if (std::abs(sum.coeff()) >= 1e-10) {
				result.push_back(sum);
			}
			it1++;
			it2++;
		}
		else if (*it1 > *it2) {
			result.push_back(*it1);
			it1++;
		}
		else {
			result.push_back(*it2);
			it2++;
		}
	}

	while (it1 != _polynom.end()) {
		result.push_back(*it1);
		it1++;
	}
	while (it2 != other._polynom.end()) {
		result.push_back(*it2);
		it2++;
	}

	_polynom = result;
	//_polynom = std::move(result);
	return *this;
}

Polynom& Polynom::operator-=(const Polynom& other) {
	List<Monom> result;
	auto it1 = _polynom.begin();
	auto it2 = other._polynom.begin();

	while (it1 != _polynom.end() && it2 != other._polynom.end()) {
		if (*it1 == *it2) {
			Monom sum = *it1 - *it2;
			if (std::abs(sum.coeff()) >= 1e-10) {
				result.push_back(sum);
			}
			it1++;
			it2++;
		}
		else if (*it1 > *it2) {
			result.push_back(*it1);
			it1++;
		}
		else {
			result.push_back(-(*it2));
			it2++;
		}
	}

	while (it1 != _polynom.end()) {
		result.push_back(*it1);
		it1++;
	}
	while (it2 != other._polynom.end()) {
		result.push_back(-(*it2));
		it2++;
	}

	_polynom = result;
	//_polynom = std::move(result);
	return *this;
}

Polynom Polynom::operator-() const noexcept {
	Polynom res(*this);
	for (auto it = res._polynom.begin(); it != res._polynom.end(); it++) {
		(*it) = -(*it);
	}
	return res;
}

void PolynomParser::ordered_insert_monom(List<Monom>& result, const Monom& monom) {
	if (result.is_empty()) {
		result.push_back(monom);
		return;
	}
	if (monom > *result.begin()) {
		result.push_front(monom);
		return;
	}

	for (auto it = result.begin(); it != result.end(); ++it) {
		auto next = it;
		++next;

		if (monom == *it) {
			*it = (*it) + monom;
			return;
		}
		if (next == result.end()) {
			result.push_back(monom);
			return;
		}
		if (monom > *next && monom < *it) {
			result.insert(it.current(), monom);
			return;
		}
	}
}

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
	for (size_t i = 0; i < new_str.size(); ) {
		try {
			Monom monom = MonomParser::parse(new_str, i);
			ordered_insert_monom(result, monom); // надо попа рядку
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
List<Monom>& Polynom::monoms() {
	return _polynom;
}
void Polynom::set_name(const std::string& name) {
	_name = name;
}
