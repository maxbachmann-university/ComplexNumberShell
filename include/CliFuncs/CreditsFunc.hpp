#pragma once
#include "CliFunc.hpp"
#include <iostream>

/**
 * @brief Output credits.
 */
class CreditsFunc : public CliFunc {
public:
  CreditsFunc() : CliFunc("credits")
  {}

  call_result call_impl(const arg_list& args) const override
  {
    std::cout << "Created by:\n"
              << "    Bachmann Maximilian\n"
              << "    Eisenmann Marvin\n"
              << "    Vetter Florian\n";
    return {};
  }

  std::string docstring() const override
  {
    return "credits()\n"
           "    output credits\n"
           "    can not be used inside expressions";
  }
};