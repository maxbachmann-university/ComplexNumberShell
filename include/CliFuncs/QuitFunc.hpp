#pragma once
#include "CliFunc.hpp"

/**
 * @brief Leave the application.
 */
class QuitFunc : public CliFunc {
public:
  QuitFunc() : CliFunc(std::vector<std::string>{"quit", "exit"})
  {}

  call_result call_impl(const arg_list& args) const override
  {
    exit(EXIT_SUCCESS);
    return {};
  }

  std::string docstring() const override
  {
    return "quit()/exit()\n"
           "    leave the application\n"
           "    can not be used inside expressions";
  }
};
