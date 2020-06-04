#pragma once
#include "Complex.hpp"

#include "CliFuncs/CliFuncs.hpp"
#include "types.hpp"

#include <memory>
#include <vector>

class CLI {
public:
  CLI();

  void evaluate_command();
  void read_new_command();

private:
  std::string current_command;

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

  HelpFunc help_command = HelpFunc(calc_commands, global_commands);

  std::string evaluate_command_impl(std::string);

  var_mapping variable_mapping;

  call_result call_func_by_name(const std::string& func_name, std::string);

  void assign_result(const std::vector<std::string>& assignments,
                     const Complex<double> result);
};
