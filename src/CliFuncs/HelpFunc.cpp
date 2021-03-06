#include "CliFuncs/HelpFunc.hpp"
#include "Utils.hpp"

/**
 * If no argument is passed this function will print the docstring for all
 * global and calculation functions.
 * Otherwise it will print the docstring of the desired function.
 */
call_result HelpFunc::call(arg_list args, const var_mapping&) const
{
  widthstream out(200, std::cout);

  std::string object_name = "";
  if (!args.empty()) {
    object_name = lowercase(args[0]);

    if (object_name == "help") {
      out.indent(4) << *this;
      return {};
    }

    for (const auto& command : calc_commands) {
      if (command->name_cmp(object_name)) {
        out.indent(4) << *command;
        return {};
      }
    }

    for (const auto& command : global_commands) {
      if (command->name_cmp(object_name)) {
        out.indent(4) << *command;
        return {};
      }
    }
  }

  out.indent(4) << calculations_docstring << "\n"
                << assignments_docstring << "\nCommands:\n";

  out.indent(4);
  for (const auto& command : calc_commands) {
    out << *command << "\n";
  }

  out << "\n";

  for (const auto& command : global_commands) {
    out << *command << "\n";
  }
  out << *this;

  return {};
}

std::string HelpFunc::docstring() const
{
  return "help()/help(<function name>)\n"
         "    output help text for object or complete help\n"
         "    can not be used inside expressions";
};