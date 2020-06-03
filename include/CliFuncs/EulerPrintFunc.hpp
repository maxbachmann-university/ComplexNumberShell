#pragma once
#include "CliFunc.hpp"
#include <iostream>

class EulerPrintFunc : public CliFunc {
public:
  EulerPrintFunc() : CliFunc(1, 1)
  {}

  call_result call_impl(const arg_list& args) const override;

  bool name_cmp(const std::string& name) const override;

  std::string docstring() const override;
};

inline CliFunc::call_result
EulerPrintFunc::call_impl(const arg_list& args) const
{
  std::cout << ComplexShuntingYard::evaluate(args[0]).to_exponential() << "\n";
  return {};
}

inline bool EulerPrintFunc::name_cmp(const std::string& name) const
{
  return name == "euler_print";
};

inline std::string EulerPrintFunc::docstring() const
{
  return "euler_print(<complex number>)\n"
         "    print complex number in euler form\n"
         "    can not be used inside expressions";
}