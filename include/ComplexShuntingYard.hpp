#pragma once
#include "Complex.hpp"

/**
 * @brief Evaluate mathematical expression in infix notation
 * 
 * @details
 * Based on <a
 * href="https://en.wikipedia.org/wiki/Shunting-yard_algorithm">Shunting-yard
 * algorithm</a> with some modifications to work with complex numbers
 */
namespace ComplexShuntingYard {
/**
 * Evaluate a math expression from a std::string
 */
Complex<double> evaluate(std::string tokens);
}; // namespace ComplexShuntingYard