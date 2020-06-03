#pragma once
#include "CliFunc.hpp"
#include "ComplexShuntingYard.hpp"

class LogFunc : public CliFunc {
public:
  LogFunc() : CliFunc("log", 1, 1)
  {}

  call_result call_impl(const arg_list& args) const override
  {
    return log(ComplexShuntingYard::evaluate(args[0]));
  }

  std::string docstring() const override
  {
    return "log(<complex number>)\n"
           "    Return Complex natural logarithm";
  }
};

class Log10Func : public CliFunc {
public:
  Log10Func() : CliFunc("log10", 1, 1)
  {}

  call_result call_impl(const arg_list& args) const override
  {
    return log10(ComplexShuntingYard::evaluate(args[0]));
  }

  std::string docstring() const override
  {
    return "log10(<complex number>)\n"
           "    Return Complex base 10 logarithm";
  }
};