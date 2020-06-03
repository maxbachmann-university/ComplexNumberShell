#pragma once
#include "CliFunc.hpp"
#include "ComplexShuntingYard.hpp"

class ConjFunc : public CliFunc {
public:
  ConjFunc() : CliFunc(1, 1)
  {}

  call_result call_impl(const arg_list& args) const override;

  bool name_cmp(const std::string& name) const override;

  std::string docstring() const override;
};

inline CliFunc::call_result ConjFunc::call_impl(const arg_list& args) const
{
  return conj(ComplexShuntingYard::evaluate(args[0]));
}

inline bool ConjFunc::name_cmp(const std::string& name) const
{
  return name == "conj";
};

inline std::string ConjFunc::docstring() const
{
  return "conj(<complex number>)\n"
         "    Return Complex conjugate";
}