#pragma once
#include "CliFunc.hpp"
#include "ComplexShuntingYard.hpp"

class LogFunc : public CliFunc {
public:
  LogFunc() : CliFunc(1, 1)
  {}

  call_result call_impl(const arg_list& args) const override;

  bool name_cmp(const std::string& name) const override;

  std::string docstring() const override;
};

inline CliFunc::call_result LogFunc::call_impl(const arg_list& args) const
{
  return log(ComplexShuntingYard::evaluate(args[0]));
}

inline bool LogFunc::name_cmp(const std::string& name) const
{
  return name == "log";
};

inline std::string LogFunc::docstring() const
{
  return "log(<complex number>)\n"
         "    Return Complex natural logarithm";
}