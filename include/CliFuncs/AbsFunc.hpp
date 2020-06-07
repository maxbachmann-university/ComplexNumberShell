#pragma once
#include "CliFunc.hpp"
#include "ComplexShuntingYard.hpp"

/**
 * @brief Return magnitude.
 */
class AbsFunc : public CliFunc {
public:
  AbsFunc() : CliFunc("abs", 1, 1)
  {}

  call_result call_impl(const arg_list& args) const override
  {
    return abs(ComplexShuntingYard::evaluate(args[0]));
  }

  std::string docstring() const override
  {
    return "abs(<complex number>)\n"
           "    Return magnitude";
  }
};