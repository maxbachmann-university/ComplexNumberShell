#pragma once
#include "CliParser.hpp"
#include "Complex.hpp"
#include "types.hpp"

#include <exception>
#include <ostream>
#include <regex>
#include <string>
#include <unordered_map>
#include <variant>

#include <array>
#include <iostream>

/**
 * @brief Interface class for all CLI functions.
 */
struct CliFunc {
  explicit CliFunc(std::string command_name, std::size_t arg_count_min = 0,
                   std::size_t arg_count_max = 0)
      : command_names({command_name}),
        arg_count_min(arg_count_min),
        arg_count_max(arg_count_max)
  {}

  explicit CliFunc(std::vector<std::string> command_name,
                   std::size_t arg_count_min = 0, std::size_t arg_count_max = 0)
      : command_names(command_name),
        arg_count_min(arg_count_min),
        arg_count_max(arg_count_max)
  {}

  /**
   * @brief Call class for calculation and return result.
   */
  virtual call_result call(arg_list args,
                           const var_mapping& variables = {}) const;

  /**
   * Calculate and return result.
   */
  virtual call_result call_impl(const arg_list& args) const;

  /**
   * Compare name to command.
   */
  bool name_cmp(const std::string& name) const;

  /**
   * Return documentation for class.
   */
  virtual std::string docstring() const = 0;

private:
  /**
   * Check for valid arguments for function.
   */
  void args_expect(const arg_list& args, std::size_t min,
                   std::size_t max = 0) const;

  std::size_t arg_count_min;
  std::size_t arg_count_max;
  std::vector<std::string> command_names;
};

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
