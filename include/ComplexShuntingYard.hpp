#pragma once
#include "Complex.hpp"

/**
 * @brief Parsing mathematical expressions.
 * 
 * Based on <a href="https://en.wikipedia.org/wiki/Shunting-yard_algorithm">Shunting-yard algorithm</a> 
 * and modified to work with complex numbers.
 */
namespace ComplexShuntingYard {
/**
 * Calculate with complex numbers.
 */
Complex<double> evaluate(std::string tokens);
};