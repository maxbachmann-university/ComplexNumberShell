#pragma once
#include "Complex.hpp"

// based on https://en.wikipedia.org/wiki/Shunting-yard_algorithm and modified
// to work with complex numbers
namespace ComplexShuntingYard {
Complex<double> evaluate(std::string tokens);
};