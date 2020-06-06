#include "CLI.hpp"
#include "XmlCommandLogger.hpp"
#include <exception>
#include <iostream>
#include <csignal>

int main()
{
  CLI cli;
  XmlCommandLogger logger;
  while (true) {
    try {
      auto command = cli.read_new_command();
      auto result = cli.evaluate_command();
      logger.logCommand(command, result);
    }
    catch (const std::exception& e) {
      std::cout << e.what() << "\n";
    }
  }
  return 0;
}