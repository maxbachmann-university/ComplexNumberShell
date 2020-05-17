#pragma once
#include "Complex.hpp"
#include <unordered_map>


// based on https://en.wikipedia.org/wiki/Shunting-yard_algorithm and modified to work with complex numbers
class ComplexShuntingYard {
	std::string tokens;
public:
	ComplexShuntingYard(std::string tokens)
	  : tokens(tokens) {}

    void replace_exponential();
	void replace_variables(const std::unordered_map<std::string, Complex<double>>& variable_mapping);
	Complex<double> evaluate();
};