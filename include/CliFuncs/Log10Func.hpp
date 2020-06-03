#pragma once
#include "CliFunc.hpp"
#include "ComplexShuntingYard.hpp"

class Log10Func : public CliFunc {
public:
  Log10Func() : CliFunc(1, 1)
  {}

  call_result call_impl(const arg_list& args) const override;

  bool name_cmp(const std::string& name) const override;

  std::string docstring() const override;
};

inline CliFunc::call_result Log10Func::call_impl(const arg_list& args) const
{
  return log10(ComplexShuntingYard::evaluate(args[0]));
}

inline bool Log10Func::name_cmp(const std::string& name) const
{
  return name == "log10";
};

inline std::string Log10Func::docstring() const
{
  return "log10(<complex number>)\n"
         "    Return Complex base 10 logarithm";
}