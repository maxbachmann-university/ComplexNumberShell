#pragma once
#include "CliFunc.hpp"
#include "ComplexShuntingYard.hpp"

class TanhFunc : public CliFunc {
public:
  TanhFunc() : CliFunc(1, 1)
  {}

  call_result call_impl(const arg_list& args) const override;

  bool name_cmp(const std::string& name) const override;

  std::string docstring() const override;
};

inline CliFunc::call_result TanhFunc::call_impl(const arg_list& args) const
{
  return tanh(ComplexShuntingYard::evaluate(args[0]));
}

inline bool TanhFunc::name_cmp(const std::string& name) const
{
  return name == "tanh";
};

inline std::string TanhFunc::docstring() const
{
  return "tanh(<complex number>)\n"
         "    Return Complex hyperbolic tangent";
}