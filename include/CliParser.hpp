#pragma once
#include <algorithm>
#include <regex>
#include <string>
#include <vector>

#include "Complex.hpp"
#include "Utils.hpp"
#include "types.hpp"
#include <unordered_map>

/**
 * @brief Parsing and checking user's input.
 */
namespace CliParser {

/**
 * @brief Expression of matching patterns for sequences of characters.
 * 
 * Needed for matching of user's input.
 * <a href="http://www.cplusplus.com/reference/regex/">C++ Reference regex</a>
 */
namespace details {
static std::regex
    var_regex(R"(([\(\*\/\+\-]|^)([a-zA-Z_][\w]*)([\)\*\/\+\-]|$))");
}

/**
 * @brief Holds the position of a function in the user's input.
 */
struct FuncPos {
  std::size_t op_start;
  std::size_t bracket_start;
  std::size_t bracket_end;
  FuncPos(std::size_t op_start, std::size_t bracket_start,
          std::size_t bracket_end)
      : op_start(op_start),
        bracket_start(bracket_start),
        bracket_end(bracket_end)
  {}
};

/**
 * @brief Holds assignments and a command of the user's input.
 */
struct Assignment {
  std::vector<std::string> assignments;
  std::string command;
  Assignment(std::vector<std::string> assignments, std::string command)
      : assignments(std::move(assignments)), command(std::move(command))
  {}
};

/**
 * @brief Substitutes variables in input command.
 */
void subsitute_variables(std::string& command, const var_mapping& variables);

/**
 * @brief Finds functions on top level in user's input.
 */
std::vector<FuncPos> find_top_level_function_calls(std::string sample);

/**
 * @brief Checks the assignments for allowed syntax.
 */
void validate_assignments(const std::vector<std::string>& assignments);

/**
 * @brief Splitting assignments and command and return them.
 */
Assignment split_assignments(const std::string& assignment);

/**
 * @brief Splitting arguments and return them.
 */
std::vector<std::string> split_args(const std::string& args);
}; // namespace CliParser