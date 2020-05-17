#pragma once
#include "Complex.hpp"
#include <unordered_map>


// based on https://en.wikipedia.org/wiki/Shunting-yard_algorithm and modified to work with complex numbers
class ComplexShuntingYard {
public:
	ComplexShuntingYard(std::string tokens, std::unordered_map<std::string, Complex<double>> variable_mapping)
	  : tokens(tokens), variable_mapping(variable_mapping) {}

	Complex<double> evaluate();
private:
	std::string tokens;
	Complex<double> evaluate_impl(std::string str);
	void replace_exponential();
	void subsitute_variables();
	void resolve_plus_minus();
	std::unordered_map<std::string, Complex<double>> variable_mapping;
};