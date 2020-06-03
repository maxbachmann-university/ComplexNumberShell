#pragma once
#include "CliFunc.hpp"
#include "ComplexShuntingYard.hpp"

class SinFunc : public CliFunc {
public:
  SinFunc() : CliFunc("sin", 1, 1)
  {}

  call_result call_impl(const arg_list& args) const override
  {
    return sin(ComplexShuntingYard::evaluate(args[0]));
  }

  std::string docstring() const override
  {
    return "sin(<complex number>)\n"
           "    Return Complex sine";
  }
};

class SinhFunc : public CliFunc {
public:
  SinhFunc() : CliFunc("sinh", 1, 1)
  {}

  call_result call_impl(const arg_list& args) const override
  {
    return sinh(ComplexShuntingYard::evaluate(args[0]));
  }

  std::string docstring() const override
  {
    return "sinh(<complex number>)\n"
           "    Return Complex hyperbolic sine";
  }
};

class CosFunc : public CliFunc {
public:
  CosFunc() : CliFunc("cos", 1, 1)
  {}

  call_result call_impl(const arg_list& args) const override
  {
    return cos(ComplexShuntingYard::evaluate(args[0]));
  }

  std::string docstring() const override
  {
    return "cos(<complex number>)\n"
           "    Return Complex cosine";
  }
};

class CoshFunc : public CliFunc {
public:
  CoshFunc() : CliFunc("cosh", 1, 1)
  {}

  call_result call_impl(const arg_list& args) const override
  {
    return cosh(ComplexShuntingYard::evaluate(args[0]));
  }

  std::string docstring() const override
  {
    return "cosh(<complex number>)\n"
           "    Return Complex hyperbolic cosine";
  }
};

class TanFunc : public CliFunc {
public:
  TanFunc() : CliFunc("tan", 1, 1)
  {}

  call_result call_impl(const arg_list& args) const override
  {
    return tan(ComplexShuntingYard::evaluate(args[0]));
  }

  std::string docstring() const override
  {
    return "cosh(<complex number>)\n"
           "    Return Complex tangent cosine";
  }
};

class TanhFunc : public CliFunc {
public:
  TanhFunc() : CliFunc("tanh", 1, 1)
  {}

  call_result call_impl(const arg_list& args) const override
  {
    return tanh(ComplexShuntingYard::evaluate(args[0]));
  }

  std::string docstring() const override
  {
    return "tanh(<complex number>)\n"
           "    Return Complex hyperbolic tangent";
  }
};
