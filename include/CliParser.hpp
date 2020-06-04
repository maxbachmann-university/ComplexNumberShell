#pragma once
#include <algorithm>
#include <regex>
#include <string>
#include <vector>

#include "Complex.hpp"
#include "Utils.hpp"
#include "types.hpp"
#include <unordered_map>

namespace CliParser {

namespace details {
static std::regex
    var_regex(R"(([\(\*\/\+\-]|^)([a-zA-Z_][\w]*)([\)\*\/\+\-]|$))");
}

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

struct Assignment {
  std::vector<std::string> assignments;
  std::string command;
  Assignment(std::vector<std::string> assignments, std::string command)
      : assignments(std::move(assignments)), command(std::move(command))
  {}
};

void subsitute_variables(std::string& command, const var_mapping& variables);

std::vector<FuncPos> find_top_level_function_calls(std::string sample);

void validate_assignments(const std::vector<std::string>& assignments);

Assignment split_assignments(const std::string& assignment);

std::vector<std::string> split_args(const std::string& args);
}; // namespace CliParser