#pragma once
#include "Complex.hpp"
#include "widthstream.hpp"
#include <exception>
#include <ostream>
#include <regex>
#include <string>
#include <unordered_map>
#include <variant>

#include <array>
#include <iostream>

struct CliFunc {
  using arg_list = std::vector<std::string>;
  using var_mapping = std::unordered_map<std::string, Complex<double>>;
  using call_result = std::variant<std::monostate, Complex<double>>;

  explicit CliFunc(std::string command_name, std::size_t arg_count_min = 0, std::size_t arg_count_max = 0)
      : command_names({command_name}), arg_count_min(arg_count_min), arg_count_max(arg_count_max)
  {}

  explicit CliFunc(std::vector<std::string> command_name, std::size_t arg_count_min = 0, std::size_t arg_count_max = 0)
      : command_names(command_name), arg_count_min(arg_count_min), arg_count_max(arg_count_max)
  {}

  virtual call_result call(arg_list args,
                           const var_mapping& variables = {}) const;

  virtual call_result call_impl(const arg_list& args) const;

  bool name_cmp(const std::string& name) const;

  virtual std::string docstring() const = 0;

private:
  void args_expect(const arg_list& args, std::size_t min,
                   std::size_t max = 0) const;

  void subsitute_variables(std::string& command,
                           const var_mapping& variables) const;

  std::size_t arg_count_min;
  std::size_t arg_count_max;
  std::vector<std::string> command_names;
};

inline bool CliFunc::name_cmp(const std::string& name) const
{
  return std::find(command_names.begin(), command_names.end(), name) != command_names.end();
};


inline void CliFunc::args_expect(const arg_list& args, std::size_t min,
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

inline CliFunc::call_result CliFunc::call(arg_list args,
                                          const var_mapping& variables) const
{
  args_expect(args, arg_count_min, arg_count_max);
  for (auto& arg : args) {
    subsitute_variables(arg, variables);
  }
  return call_impl(args);
}

inline CliFunc::call_result CliFunc::call_impl(const arg_list&) const
{
  return {};
}

inline void CliFunc::subsitute_variables(std::string& command,
                                         const var_mapping& variables) const
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
      if (variables.count(match.first) == 0) {
        throw std::invalid_argument("NameError: name '" + match.first +
                                    "' is not defined");
      }

      const std::string replacement = variables.at(match.first).str();
      command.replace(match.second + pos_change, match.first.length(),
                      replacement);
      pos_change += replacement.length() - match.first.length();
    }
  }
}

inline bool operator==(const CliFunc& lhs, const std::string& rhs)
{
  return lhs.name_cmp(rhs);
}

template <typename CharT, class Traits>
std::basic_ostream<CharT, Traits>&
operator<<(std::basic_ostream<CharT, Traits>& os, const CliFunc& func)
{
  return os << func.docstring();
}
