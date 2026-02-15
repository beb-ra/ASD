#pragma once
#include "../lib_list/list.h"
#include "../lib_polynom/Monom.h"

class Polynom {
	List<Monom> _polynom;
	std::string _name;
public:
	Polynom();
	Polynom(const Monom& monom);
	Polynom(std::string str);

	//операции
};