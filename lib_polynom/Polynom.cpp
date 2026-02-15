#include "Polynom.h"

Polynom::Polynom() {
	Monom zero;
	_polynom.push_back(zero);
}
Polynom::Polynom(const Monom& monom) {
	_polynom.push_back(monom);
}
Polynom::Polynom(std::string str) {
	//_polynom = Parser::parse(str);
}