#pragma once
#include "CliFunc.hpp"
#include "ComplexShuntingYard.hpp"

class PowFunc : public CliFunc {
public:
  PowFunc() : CliFunc(2, 2)
  {}

  call_result call_impl(const arg_list& args) const override;

  bool name_cmp(const std::string& name) const override;

  std::string docstring() const override;
};

inline CliFunc::call_result PowFunc::call_impl(const arg_list& args) const
{
  return pow(ComplexShuntingYard::evaluate(args[0]),
             ComplexShuntingYard::evaluate(args[1]));
}

inline bool PowFunc::name_cmp(const std::string& name) const
{
  return name == "pow";
};

inline std::string PowFunc::docstring() const
{
  return "pow(<base complex number>, <exponent complex number>)\n"
         "    Returns base^exponent";
}