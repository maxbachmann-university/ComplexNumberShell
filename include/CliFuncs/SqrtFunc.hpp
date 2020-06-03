#pragma once
#include "CliFunc.hpp"
#include "ComplexShuntingYard.hpp"

class SqrtFunc : public CliFunc {
public:
  SqrtFunc() : CliFunc(1, 1)
  {}

  call_result call_impl(const arg_list& args) const override;

  bool name_cmp(const std::string& name) const override;

  std::string docstring() const override;
};

inline CliFunc::call_result SqrtFunc::call_impl(const arg_list& args) const
{
  return sqrt(ComplexShuntingYard::evaluate(args[0]));
}

inline bool SqrtFunc::name_cmp(const std::string& name) const
{
  return name == "sqrt";
};

inline std::string SqrtFunc::docstring() const
{
  return "sqrt(<complex number>)\n"
         "    Return Complex square root";
}