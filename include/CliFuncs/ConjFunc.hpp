#pragma once
#include "CliFunc.hpp"
#include "ComplexShuntingYard.hpp"

class ConjFunc : public CliFunc {
public:
  ConjFunc() : CliFunc("conj", 1, 1)
  {}

  call_result call_impl(const arg_list& args) const override
  {
    return conj(ComplexShuntingYard::evaluate(args[0]));
  }

  std::string docstring() const override
  {
    return "conj(<complex number>)\n"
           "    Return Complex conjugate";
  }
};
