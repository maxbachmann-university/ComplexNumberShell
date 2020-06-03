#pragma once
#include "CliFunc.hpp"
#include "ComplexShuntingYard.hpp"

class NormFunc : public CliFunc {
public:
  NormFunc() : CliFunc("norm", 1, 1)
  {}

  call_result call_impl(const arg_list& args) const override
  {
    return norm(ComplexShuntingYard::evaluate(args[0]));
  }

  std::string docstring() const override
  {
    return "norm(<complex number>)\n"
           "    Return squared magnitude (field norm)";
  }
};
