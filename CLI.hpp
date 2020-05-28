#pragma once
#include "Complex.hpp"
#include <unordered_map>
#include <variant>
#include <vector>

class CLI {
public:
  CLI();

  void print_startup();
  void print_credits();
  void print_help(std::vector<std::string> args);
  void evaluate_command();
  void read_new_command();

private:
  struct FuncPos {
    std::size_t op_start;
    std::size_t bracket_start;
    std::size_t bracket_end;
    FuncPos(std::size_t op_start, std::size_t bracket_start, std::size_t bracket_end)
      : op_start(op_start), bracket_start(bracket_start), bracket_end(bracket_end){}
  };

  std::string current_command;
  std::string tokens;

  std::vector<FuncPos> find_top_level_function_calls(std::string sample);

  std::string evaluate_command_impl(std::string);

  std::unordered_map<std::string, Complex<double>> variable_mapping;

  std::variant<std::monostate, Complex<double>>
  call_func_by_name(const std::string& func_name, std::string);

  void subsitute_variables(std::string& command);

  void assign_result(const std::vector<std::string>& assignments,
                     const Complex<double> result);

  std::vector<std::string>
  split_assignments(const std::string& assignment) const;

  std::vector<std::string> split_args(const std::string& args) const;

  void args_expect(const std::vector<std::string> & args, std::size_t min, std::size_t max = 0) const;
};
