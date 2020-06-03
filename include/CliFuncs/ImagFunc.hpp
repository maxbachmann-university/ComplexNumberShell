#pragma once
#include "CliFunc.hpp"
#include "ComplexShuntingYard.hpp"

class ImagFunc : public CliFunc {
public:
  ImagFunc() : CliFunc(1, 1)
  {}

  call_result call_impl(const arg_list& args) const override;

  bool name_cmp(const std::string& name) const override;

  std::string docstring() const override;
};

inline CliFunc::call_result ImagFunc::call_impl(const arg_list& args) const
{
  return imag(ComplexShuntingYard::evaluate(args[0]));
}

inline bool ImagFunc::name_cmp(const std::string& name) const
{
  return name == "imag";
};

inline std::string ImagFunc::docstring() const
{
  return "imag(<complex number>)\n"
         "    Return imaginary component of the complex number";
}