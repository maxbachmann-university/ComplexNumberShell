#pragma once
#include "CliFunc.hpp"
#include "ComplexShuntingYard.hpp"

class SinhFunc : public CliFunc {
public:
  SinhFunc() : CliFunc(1, 1)
  {}

  call_result call_impl(const arg_list& args) const override;

  bool name_cmp(const std::string& name) const override;

  std::string docstring() const override;
};

inline CliFunc::call_result SinhFunc::call_impl(const arg_list& args) const
{
  return sinh(ComplexShuntingYard::evaluate(args[0]));
}

inline bool SinhFunc::name_cmp(const std::string& name) const
{
  return name == "sinh";
};

inline std::string SinhFunc::docstring() const
{
  return "sinh(<complex number>)\n"
         "    Return Complex hyperbolic sine";
}