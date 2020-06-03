#pragma once
#include "CliFunc.hpp"
#include <iostream>

class CreditsFunc : public CliFunc {
public:
  CreditsFunc() : CliFunc()
  {}

  call_result call_impl(const arg_list& args) const override;

  bool name_cmp(const std::string& name) const override;

  std::string docstring() const override;
};

inline CliFunc::call_result CreditsFunc::call_impl(const arg_list& args) const
{
  std::cout << "Created by:\n"
            << "    Bachmann Maximilian\n"
            << "    Eisenmann Marvin\n"
            << "    Vetter Florian\n";
  return {};
}

inline bool CreditsFunc::name_cmp(const std::string& name) const
{
  return name == "credits";
};

inline std::string CreditsFunc::docstring() const
{
  return "credits()\n"
         "    output credits\n"
         "    can not be used inside expressions";
}