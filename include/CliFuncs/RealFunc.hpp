#pragma once
#include "CliFunc.hpp"
#include "ComplexShuntingYard.hpp"

class RealFunc : public CliFunc {
public:
  RealFunc() : CliFunc(1, 1)
  {}

  call_result call_impl(const arg_list& args) const override;

  bool name_cmp(const std::string& name) const override;

  std::string docstring() const override;
};

inline CliFunc::call_result RealFunc::call_impl(const arg_list& args) const
{
  return real(ComplexShuntingYard::evaluate(args[0]));
}

inline bool RealFunc::name_cmp(const std::string& name) const
{
  return name == "real";
};

inline std::string RealFunc::docstring() const
{
  return "real(<complex number>)\n"
         "    Return real component of the complex number";
}