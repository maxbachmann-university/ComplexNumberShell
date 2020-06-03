#pragma once
#include "CliFunc.hpp"
#include "ComplexShuntingYard.hpp"

class SqrtFunc : public CliFunc {
public:
  SqrtFunc() : CliFunc("sqrt", 1, 1)
  {}

  call_result call_impl(const arg_list& args) const override
  {
    return sqrt(ComplexShuntingYard::evaluate(args[0]));
  }

  std::string docstring() const override
  {
    return "sqrt(<complex number>)\n"
           "    Return Complex square root";
  }
};
