#pragma once
#include "CliFunc.hpp"

class QuitFunc : public CliFunc {
public:
  QuitFunc() : CliFunc()
  {}

  call_result call_impl(const arg_list& args) const override;

  bool name_cmp(const std::string& name) const override;

  std::string docstring() const override;
};

inline CliFunc::call_result QuitFunc::call_impl(const arg_list& args) const
{
  exit(EXIT_SUCCESS);
  return {};
}

inline bool QuitFunc::name_cmp(const std::string& name) const
{
  return name == "quit" || name == "exit";
};

inline std::string QuitFunc::docstring() const
{
  return "quit()/exit()\n"
         "    leave the application\n"
         "    can not be used inside expressions";
}