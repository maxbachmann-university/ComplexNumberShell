#pragma once
#include "CliFunc.hpp"
#include "ComplexShuntingYard.hpp"

class ExpFunc : public CliFunc {
public:
  ExpFunc() : CliFunc(1, 1)
  {}

  call_result call_impl(const arg_list& args) const override;

  bool name_cmp(const std::string& name) const override;

  std::string docstring() const override;
};

inline CliFunc::call_result ExpFunc::call_impl(const arg_list& args) const
{
  return exp(ComplexShuntingYard::evaluate(args[0]));
}

inline bool ExpFunc::name_cmp(const std::string& name) const
{
  return name == "exp";
};

inline std::string ExpFunc::docstring() const
{
  return "exp(<complex number>)\n"
         "    Return Complex base e exponential";
}