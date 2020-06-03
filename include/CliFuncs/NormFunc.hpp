#pragma once
#include "CliFunc.hpp"
#include "ComplexShuntingYard.hpp"

class NormFunc : public CliFunc {
public:
  NormFunc() : CliFunc(1, 1)
  {}

  call_result call_impl(const arg_list& args) const override;

  bool name_cmp(const std::string& name) const override;

  std::string docstring() const override;
};

inline CliFunc::call_result NormFunc::call_impl(const arg_list& args) const
{
  return norm(ComplexShuntingYard::evaluate(args[0]));
}

inline bool NormFunc::name_cmp(const std::string& name) const
{
  return name == "norm";
};

inline std::string NormFunc::docstring() const
{
  return "norm(<complex number>)\n"
         "    Return squared magnitude (field norm)";
}