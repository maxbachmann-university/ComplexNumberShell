#pragma once
#include "CliFunc.hpp"
#include "ComplexShuntingYard.hpp"

class SinFunc : public CliFunc {
public:
  SinFunc() : CliFunc(1, 1)
  {}

  call_result call_impl(const arg_list& args) const override;

  bool name_cmp(const std::string& name) const override;

  std::string docstring() const override;
};

inline CliFunc::call_result SinFunc::call_impl(const arg_list& args) const
{
  return sin(ComplexShuntingYard::evaluate(args[0]));
}

inline bool SinFunc::name_cmp(const std::string& name) const
{
  return name == "sin";
};

inline std::string SinFunc::docstring() const
{
  return "sin(<complex number>)\n"
         "    Return Complex sine";
}