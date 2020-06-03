#pragma once
#include "CliFunc.hpp"
#include "ComplexShuntingYard.hpp"

class AbsFunc : public CliFunc {
public:
  AbsFunc() : CliFunc(1, 1)
  {}

  call_result call_impl(const arg_list& args) const override;

  bool name_cmp(const std::string& name) const override;

  std::string docstring() const override;
};

inline CliFunc::call_result AbsFunc::call_impl(const arg_list& args) const
{
  return abs(ComplexShuntingYard::evaluate(args[0]));
}

inline bool AbsFunc::name_cmp(const std::string& name) const
{
  return name == "abs";
};

inline std::string AbsFunc::docstring() const
{
  return "abs(<complex number>)\n"
         "    Return magnitude";
}