#include "CLI.hpp"
#include "ComplexShuntingYard.hpp"
#include <exception>
#include <iostream>
#include <regex>

template <class... Ts> struct overload : Ts... {
  using Ts::operator()...;
};
template <class... Ts> overload(Ts...) -> overload<Ts...>;

bool is_char_underscore(char x)
{
  return (x == '_') || (x >= 'A' && x <= 'Z') || (x >= 'a' && x <= 'z');
}

bool is_num_char_underscore(char x)
{
  return is_char_underscore(x) || (x >= '0' && x <= '9');
}

CLI::CLI()
{
  print_startup();
}

void CLI::evaluate_command()
{
  if (tokens.empty()) {
    return;
  }
  std::vector<std::string> assignments = split_assignments(tokens);
  tokens = assignments.back();
  assignments.pop_back();

  auto methods = find_top_level_function_calls(tokens);

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

  subsitute_variables(tokens);
  assign_result(assignments, ComplexShuntingYard::evaluate(tokens));
}

std::vector<CLI::FuncPos> CLI::find_top_level_function_calls(std::string sample)
{
  std::vector<FuncPos> characterLocations;
  std::size_t word_start = 0;
  std::size_t word_len = 0;
  std::size_t bracket_start = 0;
  std::size_t bracket_count = 0;
  for (std::size_t i = 0; i < sample.size(); i++) {
    if (sample[i] == '(') {
      if (bracket_count) {
        ++bracket_count;
      }
      else if (word_len + word_start == i) {
        bracket_count = 1;
        bracket_start = i;
      }
      else {
        word_len = 0;
        word_start = 0;
      }
    }
    else if (sample[i] == ')') {
      if (bracket_count) {
        --bracket_count;
      }

      if (!bracket_count && word_len) {
        characterLocations.emplace_back(word_start, bracket_start, i);
      }
    }
    else if (!word_len && is_char_underscore(sample[i])) {
      word_len = 1;
      word_start = i;
    }
    else if (word_len && is_num_char_underscore(sample[i])) {
      word_len += 1;
    }
    else if (!bracket_count) {
      word_len = 0;
      word_start = 0;
    }
  }

  return characterLocations;
}

void CLI::subsitute_variables(std::string& command)
{
  // execute twice to catch all variables e.g. a*a -> (<complex>)*a ->
  // (<complex>)*(<complex>)
  for (int i = 0; i < 2; ++i) {
    const std::regex var_regex(
        R"(([\(\*\/\+\-]|^)([a-zA-Z_][\w]*)([\)\*\/\+\-]|$))");
    const auto var_begin =
        std::sregex_iterator(command.begin(), command.end(), var_regex);
    std::vector<std::pair<std::string, std::size_t>> matches;

    for (auto i = var_begin; i != std::sregex_iterator(); ++i) {
      std::smatch match = *i;
      matches.emplace_back(match[2].str(), match.position(2));
    }

    signed int pos_change = 0;
    for (const auto& match : matches) {
      if (variable_mapping.count(match.first) == 0) {
        throw std::invalid_argument("NameError: name '" + match.first +
                                    "' is not defined");
      }

      const std::string replacement = variable_mapping.at(match.first).str();
      command.replace(match.second + pos_change, match.first.length(),
                      replacement);
      pos_change += replacement.length() - match.first.length();
    }
  }
}

std::string CLI::evaluate_command_impl(std::string inner_tokens)
{
  auto methods = find_top_level_function_calls(inner_tokens);

  for (auto method_iter = methods.rbegin(); method_iter != methods.rend();
       ++method_iter)
  {
    const auto method = *method_iter;
    std::size_t op_start = method.op_start;
    std::size_t op_len = method.bracket_start - method.op_start;
    std::size_t args_start = method.bracket_start + 1;
    std::size_t args_len = method.bracket_end - method.bracket_start - 1;

    std::string op = inner_tokens.substr(op_start, op_len);
    std::string args = inner_tokens.substr(args_start, args_len);

    std::string eval_args = evaluate_command_impl(args);
    const auto result = call_func_by_name(op, eval_args);

    if (result.index() == 0) {
      throw std::invalid_argument("SyntaxError: can't call with None Type");
    }

    const std::string replacement = std::get<1>(result).str();
    inner_tokens.replace(op_start, op_len + args_len + 2, replacement);
  }

  return inner_tokens;
}

void CLI::read_new_command()
{
  std::cout << ">>> ";
  std::string command;
  std::getline(std::cin, command);
  // removing whitespace in assignment should not happen!!!
  command.erase(std::remove_if(command.begin(), command.end(),
                               [](char x) { return std::isspace(x); }),
                command.end());
  tokens = current_command = command;
}

void CLI::assign_result(const std::vector<std::string>& assignments,
                        const Complex<double> result)
{
  if (assignments.empty()) {
    std::cout << result << "\n";
    return;
  }

  for (const auto& assignment : assignments) {
    if (assignment[0] >= '0' && assignment[0] <= '9') {
      if (assignment.length() == 1) {
        throw std::invalid_argument("SyntaxError: can't assign to literal");
      }
      throw std::invalid_argument("SyntaxError: invalid syntax");
    }
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

std::vector<std::string>
CLI::split_assignments(const std::string& assignment) const
{
  std::vector<std::string> output;

  auto first = assignment.data(), second = assignment.data(),
       last = first + assignment.size();
  for (; second != last && first != last; first = second + 1) {
    second =
        std::find_if(first, last, [](const char& ch) { return ch == '='; });

    if (first != second) {
      output.emplace_back(first, second - first);
    }
  }

  return output;
}

std::vector<std::string> CLI::split_args(const std::string& args) const
{
  std::vector<std::string> output;

  auto first = args.data(), second = args.data(), last = first + args.size();
  for (; second != last && first != last; first = second + 1) {
    second =
        std::find_if(first, last, [](const char& ch) { return ch == ','; });

    if (first != second) {
      output.emplace_back(first, second - first);
    }
  }

  return output;
}

std::variant<std::monostate, Complex<double>>
CLI::call_func_by_name(const std::string& func_name, std::string args)
{
  auto arg_list = split_args(args);

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

  if (help_command->name_cmp(func_name)) {
    return help_command->call(arg_list);
    ;
  }
  throw std::invalid_argument("NameError: name '" + func_name +
                              "' is not defined");
}

void CLI::print_startup()
{
  std::cout << "Welcome to the Complex Number Shell\n"
            << "type \"help()\", \"credits()\" for more information.\n";
}