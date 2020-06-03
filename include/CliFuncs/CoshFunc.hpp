#pragma once
#include "CliFunc.hpp"
#include "ComplexShuntingYard.hpp"

class CoshFunc : public CliFunc {
public:
  CoshFunc() : CliFunc(1, 1)
  {}

  call_result call_impl(const arg_list& args) const override;

  bool name_cmp(const std::string& name) const override;

  std::string docstring() const override;
};

inline CliFunc::call_result CoshFunc::call_impl(const arg_list& args) const
{
  return cosh(ComplexShuntingYard::evaluate(args[0]));
}

inline bool CoshFunc::name_cmp(const std::string& name) const
{
  return name == "cosh";
};

inline std::string CoshFunc::docstring() const
{
  return "cosh(<complex number>)\n"
         "    Return Complex hyperbolic cosine";
}