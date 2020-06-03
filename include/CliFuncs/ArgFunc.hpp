#pragma once
#include "CliFunc.hpp"
#include "ComplexShuntingYard.hpp"

class ArgFunc : public CliFunc {
public:
  ArgFunc() : CliFunc(1, 1)
  {}

  call_result call_impl(const arg_list& args) const override;

  bool name_cmp(const std::string& name) const override;

  std::string docstring() const override;
};

inline CliFunc::call_result ArgFunc::call_impl(const arg_list& args) const
{
  return arg(ComplexShuntingYard::evaluate(args[0]));
}

inline bool ArgFunc::name_cmp(const std::string& name) const
{
  return name == "abs";
};

inline std::string ArgFunc::docstring() const
{
  return "arg(<complex number>)\n"
         "    Return phase angle";
}