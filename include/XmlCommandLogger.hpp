#pragma once

#include <string>

#include "tinyxml2/tinyxml2.h"

#include "types.hpp"

class XmlCommandLogger {
public:
  XmlCommandLogger();

  void logCommand(std::string command, call_result result);

private:
  std::string generate_filename() const;
  std::string filename;
  tinyxml2::XMLDocument xmlDoc;
  tinyxml2::XMLNode* root;
  tinyxml2::XMLElement* commands;
};