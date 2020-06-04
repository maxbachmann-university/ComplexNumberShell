#include "CliFuncs/HelpFunc.hpp"
#include "Utils.hpp"

call_result HelpFunc::call(arg_list args, const var_mapping&) const
{
  widthstream out(200, std::cout);

  std::string object_name = "";
  if (!args.empty()) {
    object_name = lowercase(args[0]);

    if (object_name == "help") {
      out.indent(4) << docstring();
      return {};
    }

    for (const auto& command : calc_commands) {
      if (command->name_cmp(object_name)) {
        out.indent(4) << command->docstring();
        return {};
      }
    }

    for (const auto& command : global_commands) {
      if (command->name_cmp(object_name)) {
        out.indent(4) << command->docstring();
        return {};
      }
    }
  }

  out.indent(4) << calculations_docstring << "\n"
                << assignments_docstring << "\nCommands:\n";

  out.indent(4);
  for (const auto& command : calc_commands) {
    out << command->docstring() << "\n";
  }

  out << "\n";

  for (const auto& command : global_commands) {
    out << command->docstring() << "\n";
  }
  out << docstring();

  return {};
}

std::string HelpFunc::docstring() const
{
  return "help()/help(<function name>)\n"
         "    output help text for object or complete help\n"
         "    can not be used inside expressions";
};