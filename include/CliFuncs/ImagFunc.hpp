#pragma once
#include "CliFunc.hpp"
#include "ComplexShuntingYard.hpp"

/**
 * @brief Return imaginary component of the complex number.
 */
class ImagFunc : public CliFunc {
public:
  ImagFunc() : CliFunc("imag", 1, 1)
  {}

  call_result call_impl(const arg_list& args) const override
  {
    return imag(ComplexShuntingYard::evaluate(args[0]));
  }

  std::string docstring() const override
  {
    return "imag(<complex number>)\n"
           "    Return imaginary component of the complex number";
  }
};
