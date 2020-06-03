#pragma once
#include "CliFunc.hpp"
#include "ComplexShuntingYard.hpp"

class ArgFunc : public CliFunc {
public:
  ArgFunc() : CliFunc("arg", 1, 1)
  {}

  call_result call_impl(const arg_list& args) const override
  {
    return arg(ComplexShuntingYard::evaluate(args[0]));
  }

  std::string docstring() const override
  {
    return "arg(<complex number>)\n"
           "    Return phase angle";
  }
};
