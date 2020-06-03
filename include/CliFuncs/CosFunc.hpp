#pragma once
#include "CliFunc.hpp"
#include "ComplexShuntingYard.hpp"

class CosFunc : public CliFunc {
public:
  CosFunc() : CliFunc(1, 1)
  {}

  call_result call_impl(const arg_list& args) const override;

  bool name_cmp(const std::string& name) const override;

  std::string docstring() const override;
};

inline CliFunc::call_result CosFunc::call_impl(const arg_list& args) const
{
  return cos(ComplexShuntingYard::evaluate(args[0]));
}

inline bool CosFunc::name_cmp(const std::string& name) const
{
  return name == "cos";
};

inline std::string CosFunc::docstring() const
{
  return "cos(<complex number>)\n"
         "    Return Complex cosine";
}