#include "CLI.hpp"
#include "CliParser.hpp"
#include "ComplexShuntingYard.hpp"
#include "Utils.hpp"
#include <exception>
#include <iostream>

CLI::CLI()
{
  std::cout << "Welcome to the Complex Number Shell\n"
            << "type \"help()\", \"credits()\" for more information.\n";
}

void CLI::evaluate_command()
{
  if (current_command.empty()) {
    return;
  }
  auto assignment = CliParser::split_assignments(current_command);
  auto assignments = assignment.assignments;
  auto tokens = assignment.command;

  auto methods = CliParser::find_top_level_function_calls(tokens);

  for (auto method_iter = methods.rbegin(); method_iter != methods.rend();
       ++method_iter)
  {
    const auto method = *method_iter;
    std::size_t op_start = method.op_start;
    std::size_t op_len = method.bracket_start - method.op_start;
    std::size_t args_start = method.bracket_start + 1;
    std::size_t args_len = method.bracket_end - method.bracket_start - 1;

    std::string op = tokens.substr(op_start, op_len);
    std::string args = tokens.substr(args_start, args_len);

    std::string eval_args = evaluate_command_impl(args);
    const auto result = call_func_by_name(op, eval_args);

    if (result.index() == 0) {
      if (methods.size() > 1) {
        throw std::invalid_argument("SyntaxError: can't call with None");
      }
      if (!assignments.empty()) {
        throw std::invalid_argument("SyntaxError: can't assign None Type");
      }
      return;
    }

    const std::string replacement = std::get<1>(result).str();
    tokens.replace(op_start, op_len + args_len + 2, replacement);
  }

  CliParser::subsitute_variables(tokens, variable_mapping);
  assign_result(assignments, ComplexShuntingYard::evaluate(tokens));
}

std::string CLI::evaluate_command_impl(std::string tokens)
{
  auto methods = CliParser::find_top_level_function_calls(tokens);

  for (auto method_iter = methods.rbegin(); method_iter != methods.rend();
       ++method_iter)
  {
    const auto method = *method_iter;
    std::size_t op_start = method.op_start;
    std::size_t op_len = method.bracket_start - method.op_start;
    std::size_t args_start = method.bracket_start + 1;
    std::size_t args_len = method.bracket_end - method.bracket_start - 1;

    std::string op = tokens.substr(op_start, op_len);
    std::string args = tokens.substr(args_start, args_len);

    std::string eval_args = evaluate_command_impl(args);
    const auto result = call_func_by_name(op, eval_args);

    if (result.index() == 0) {
      throw std::invalid_argument("SyntaxError: can't call with None Type");
    }

    const std::string replacement = std::get<1>(result).str();
    tokens.replace(op_start, op_len + args_len + 2, replacement);
  }

  return tokens;
}

void CLI::read_new_command()
{
  std::cout << ">>> ";
  std::getline(std::cin, current_command);
  current_command = strip(current_command);
}

void CLI::assign_result(const std::vector<std::string>& assignments,
                        const Complex<double> result)
{
  if (assignments.empty()) {
    std::cout << result << "\n";
    return;
  }

  for (const auto& assignment : assignments) {
    std::size_t comma_pos = 0;
    for (std::size_t i = 0; i < assignment.length(); ++i) {
      const char ch = assignment[i];
      if (ch == '+' || ch == '-' || ch == '*' || ch == '/') {
        throw std::invalid_argument("SyntaxError: can't assign to operator");
      }
      if (ch == ',') {
        if (i == 0) {
          throw std::invalid_argument("SyntaxError: Invalid syntax");
        }
        if (comma_pos) {
          throw std::invalid_argument(
              "SyntaxError: can only unpack complex to 1 or 2 variables");
        }
        comma_pos = i;
      }
    }

    if (comma_pos) {
      variable_mapping[assignment.substr(0, comma_pos)] = real(result);
      variable_mapping[assignment.substr(comma_pos + 1)] =
          Complex<double>(0, imag(result));
    }
    else {
      variable_mapping[assignment] = result;
    }
  }
}

call_result CLI::call_func_by_name(const std::string& func_name, std::string args)
{
  auto arg_list = CliParser::split_args(args);

  for (const auto& command : calc_commands) {
    if (command->name_cmp(func_name)) {
      return command->call(arg_list, variable_mapping);
    }
  }

  for (const auto& command : global_commands) {
    if (command->name_cmp(func_name)) {
      return command->call(arg_list, variable_mapping);
    }
  }

  if (help_command.name_cmp(func_name)) {
    return help_command.call(arg_list, variable_mapping);
  }
  throw std::invalid_argument("NameError: name '" + func_name +
                              "' is not defined");
}