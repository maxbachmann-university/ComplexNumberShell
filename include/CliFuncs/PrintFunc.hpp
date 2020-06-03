#pragma once
#include "CliFunc.hpp"
#include <iostream>

class PrintFunc : public CliFunc {
public:
  PrintFunc()
      : CliFunc(std::vector<std::string>{"print", "cartesian_print"}, 1, 1)
  {}

  call_result call_impl(const arg_list& args) const override
  {
    std::cout << ComplexShuntingYard::evaluate(args[0]) << "\n";
    return {};
  }

  std::string docstring() const override
  {
    return "print(<complex number>)/cartesian_print(<complex number>)\n"
           "    print complex number in cartesian form\n"
           "    can not be used inside expressions";
  }
};

class EulerPrintFunc : public CliFunc {
public:
  EulerPrintFunc() : CliFunc("euler_print", 1, 1)
  {}

  call_result call_impl(const arg_list& args) const override
  {
    std::cout << ComplexShuntingYard::evaluate(args[0]).to_exponential()
              << "\n";
    return {};
  }

  std::string docstring() const override
  {
    return "euler_print(<complex number>)\n"
           "    print complex number in euler form\n"
           "    can not be used inside expressions";
  }
};
