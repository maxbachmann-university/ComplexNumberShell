#pragma once
#include "CliFunc.hpp"
#include "ComplexShuntingYard.hpp"

class RealFunc : public CliFunc {
public:
  RealFunc() : CliFunc("real", 1, 1)
  {}

  call_result call_impl(const arg_list& args) const override
  {
    return real(ComplexShuntingYard::evaluate(args[0]));
  }

  std::string docstring() const override
  {
    return "real(<complex number>)\n"
           "    Return real component of the complex number";
  }
};
