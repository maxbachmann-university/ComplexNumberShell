#pragma once
#include "CliFunc.hpp"
#include "ComplexShuntingYard.hpp"

/**
 * @brief return Complex base e exponential
 */
class ExpFunc : public CliFunc {
public:
  ExpFunc() : CliFunc("exp", 1, 1)
  {}

  call_result call_impl(const arg_list& args) const override
  {
    return exp(ComplexShuntingYard::evaluate(args[0]));
  }

  std::string docstring() const override
  {
    return "exp(<complex number>)\n"
           "    Return Complex base e exponential";
  }
};
