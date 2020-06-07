#pragma once

#include <string>

#include "tinyxml2/tinyxml2.h"

#include "types.hpp"

/**
 * @brief XML Logger for all commands and results.
 */
class XmlCommandLogger {
public:
  XmlCommandLogger();

  /**
   * @brief Log a command with the result
   */
  void logCommand(std::string command, call_result result);

private:
  std::string generate_filename() const;
  std::string filename;
  tinyxml2::XMLDocument xmlDoc;
  tinyxml2::XMLNode* root;
  tinyxml2::XMLElement* commands;
};