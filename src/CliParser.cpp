#include "CliParser.hpp"

/**
 * Substitutes all variables in input command with their complex expression.
 */
void CliParser::subsitute_variables(std::string& command,
                                    const var_mapping& variables)
{
  // execute twice to catch all variables e.g. a*a -> (<complex>)*a ->
  // (<complex>)*(<complex>)
  for (int i = 0; i < 2; ++i) {
    const auto var_begin = std::sregex_iterator(command.begin(), command.end(),
                                                details::var_regex);
    std::vector<std::pair<std::string, std::size_t>> matches;

    for (auto i = var_begin; i != std::sregex_iterator(); ++i) {
      std::smatch match = *i;
      matches.emplace_back(match[2].str(), match.position(2));
    }

    int pos_change = 0;
    for (const auto& match : matches) {
      if (variables.count(match.first) == 0) {
        throw std::invalid_argument("NameError: name '" + match.first +
                                    "' is not defined");
      }

      const std::string replacement = variables.at(match.first).str();
      command.replace(match.second + pos_change, match.first.length(),
                      replacement);
      pos_change += static_cast<int>(replacement.length() - match.first.length());
    }
  }
}

/**
 * Finding the functions on the top level.
 * Returns the position of the functions including it's brackets as vector with FuncPos.
 */
std::vector<CliParser::FuncPos>
CliParser::find_top_level_function_calls(std::string sample)
{
  std::vector<FuncPos> characterLocations;
  std::size_t word_start = 0;
  std::size_t word_len = 0;
  std::size_t bracket_start = 0;
  std::size_t bracket_count = 0;
  bool is_command = false;
  for (std::size_t i = 0; i < sample.size(); i++) {
    if (sample[i] == '(') {
      if (bracket_count) {
        ++bracket_count;
      }
      else if (word_len + word_start == i) {
        is_command = true;
        bracket_count = 1;
        bracket_start = i;
      }
      else {
        word_len = 0;
        word_start = 0;
      }
    }
    else if (is_command && sample[i] == ')') {
      if (bracket_count) {
        --bracket_count;
      }

      if (!bracket_count && word_len) {
        characterLocations.emplace_back(word_start, bracket_start, i);
      }
    }
    else if (!word_len && is_char_underscore(sample[i])) {
      is_command = false;
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

void CliParser::validate_assignments(
    const std::vector<std::string>& assignments)
{
  for (const auto& assignment : assignments) {
    if (std::regex_match(assignment, details::var_regex)) {
      continue;
    }

    if (assignment.length() == 1 && assignment[0] >= '0' &&
        assignment[0] <= '9') {
      throw std::invalid_argument("SyntaxError: can't assign to literal");
    }
    throw std::invalid_argument("SyntaxError: invalid syntax");
  }
}

CliParser::Assignment
CliParser::split_assignments(const std::string& assignment)
{
  std::vector<std::string> assignments;

  auto first = assignment.data(), second = assignment.data(),
       last = first + assignment.size();
  for (; second != last && first != last; first = second + 1) {
    second =
        std::find_if(first, last, [](const char& ch) { return ch == '='; });

    if (first != second) {
      assignments.push_back(strip(std::string(first, second - first)));
    }
  }

  std::string command = remove_whitespace(assignments.back());
  assignments.pop_back();
  validate_assignments(assignments);
  return {assignments, command};
}

std::vector<std::string> CliParser::split_args(const std::string& args)
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