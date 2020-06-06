#include "CliFunc.hpp"

bool CliFunc::name_cmp(const std::string& name) const
{
  return std::find(command_names.begin(), command_names.end(), name) !=
         command_names.end();
};

void CliFunc::args_expect(const arg_list& args, std::size_t min,
                                 std::size_t max) const
{
  if (args.size() < min || args.size() > max) {
    if (min == max) {
      throw std::invalid_argument("TypeError: function expected '" +
                                  std::to_string(min) + "' arguments");
    }

    throw std::invalid_argument("TypeError: function expected between '" +
                                std::to_string(min) + "' and '" +
                                std::to_string(max) + "' arguments");
  }
}

/**
 * Substitute all variables and return calculated result of CliFunc::call_impl.
 */
call_result CliFunc::call(arg_list args,
                                          const var_mapping& variables) const
{
  args_expect(args, arg_count_min, arg_count_max);
  for (auto& arg : args) {
    CliParser::subsitute_variables(arg, variables);
  }
  return call_impl(args);
}

call_result CliFunc::call_impl(const arg_list&) const
{
  return {};
}
