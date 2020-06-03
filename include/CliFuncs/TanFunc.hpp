#pragma once
#include "CliFunc.hpp"
#include "ComplexShuntingYard.hpp"

class TanFunc : public CliFunc {
public:
  TanFunc() : CliFunc(1, 1)
  {}

  call_result call_impl(const arg_list& args) const override;

  bool name_cmp(const std::string& name) const override;

  std::string docstring() const override;
};

inline CliFunc::call_result TanFunc::call_impl(const arg_list& args) const
{
  return tan(ComplexShuntingYard::evaluate(args[0]));
}

inline bool TanFunc::name_cmp(const std::string& name) const
{
  return name == "tan";
};

inline std::string TanFunc::docstring() const
{
  return "cosh(<complex number>)\n"
         "    Return Complex tangent cosine";
}