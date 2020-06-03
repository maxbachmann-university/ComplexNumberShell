#pragma once
#include "CliFunc.hpp"
#include <iostream>

class PrintFunc : public CliFunc {
public:
  PrintFunc() : CliFunc(1, 1)
  {}

  call_result call_impl(const arg_list& args) const override;

  bool name_cmp(const std::string& name) const override;

  std::string docstring() const override;
};

inline CliFunc::call_result PrintFunc::call_impl(const arg_list& args) const
{
  std::cout << ComplexShuntingYard::evaluate(args[0]) << "\n";
  return {};
}

inline bool PrintFunc::name_cmp(const std::string& name) const
{
  return name == "print" || name == "cartesian_print";
};

inline std::string PrintFunc::docstring() const
{
  return "print(<complex number>)/cartesian_print(<complex number>)\n"
         "    print complex number in cartesian form\n"
         "    can not be used inside expressions";
}