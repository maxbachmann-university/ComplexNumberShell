#pragma once
#include "Complex.hpp"

#include "CliFuncs/CliFuncs.hpp"

#include <memory>
#include <unordered_map>
#include <variant>
#include <vector>

class CLI {
public:
  CLI();

  void print_startup();
  void evaluate_command();
  void read_new_command();

private:
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

  std::string current_command;
  std::string tokens;

  std::vector<std::shared_ptr<CliFunc>> calc_commands{
      std::make_shared<AbsFunc>(),  std::make_shared<PowFunc>(),
      std::make_shared<ArgFunc>(),  std::make_shared<RealFunc>(),
      std::make_shared<ImagFunc>(), std::make_shared<NormFunc>(),
      std::make_shared<ConjFunc>(), std::make_shared<CosFunc>(),
      std::make_shared<CoshFunc>(), std::make_shared<ExpFunc>(),
      std::make_shared<LogFunc>(),  std::make_shared<Log10Func>(),
      std::make_shared<SinFunc>(),  std::make_shared<SinhFunc>(),
      std::make_shared<TanFunc>(),  std::make_shared<TanhFunc>(),
      std::make_shared<SqrtFunc>()};

  std::vector<std::shared_ptr<CliFunc>> global_commands = {
      std::make_shared<CreditsFunc>(), std::make_shared<QuitFunc>(),
      std::make_shared<PrintFunc>(), std::make_shared<EulerPrintFunc>()};

  std::shared_ptr<CliFunc> help_command =
      std::make_shared<HelpFunc>(calc_commands, global_commands);

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
};