#pragma once
#include "CliFunc.hpp"
#include "ComplexShuntingYard.hpp"

/**
 * @brief Returns base^exponent.
 */
class PowFunc : public CliFunc {
public:
  PowFunc() : CliFunc("pow", 2, 2)
  {}

  call_result call_impl(const arg_list& args) const override
  {
    return pow(ComplexShuntingYard::evaluate(args[0]),
               ComplexShuntingYard::evaluate(args[1]));
  }

  std::string docstring() const override
  {
    return "pow(<base complex number>, <exponent complex number>)\n"
           "    Returns base^exponent";
  }
};
