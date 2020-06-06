#include "XmlCommandLogger.hpp"

#include <ctime>
#include <iomanip>
#include <ostream>

XmlCommandLogger::XmlCommandLogger()
{
  filename = generate_filename();
  root = xmlDoc.NewElement("ShellLog");
  commands = xmlDoc.NewElement("Commands");
  xmlDoc.InsertFirstChild(root);
  xmlDoc.SaveFile(filename.data());
}

/**
 * Logging all commands and their result.
 * This includes results in cartesian and euler form.
 */
void XmlCommandLogger::logCommand(std::string command, call_result result)
{
  tinyxml2::XMLElement* commandItem = xmlDoc.NewElement("Command");
  commandItem->SetText(command.data());

  tinyxml2::XMLElement* commandResult = xmlDoc.NewElement("Result");

  switch (result.index()) {
  case 0:
    commandResult->SetText("None");
    break;
  case 1:
    auto complexNumber = std::get<1>(result);

    tinyxml2::XMLElement* cartesianResult = xmlDoc.NewElement("CartesianForm");
    cartesianResult->SetText(complexNumber.str().data());
    commandResult->InsertEndChild(cartesianResult);

    tinyxml2::XMLElement* eulerResult = xmlDoc.NewElement("EulerForm");
    eulerResult->SetText(complexNumber.to_exponential().str().data());
    commandResult->InsertEndChild(eulerResult);
    break;
  }

  commandItem->InsertEndChild(commandResult);
  root->InsertEndChild(commandItem);
  xmlDoc.SaveFile(filename.data());
}

std::string XmlCommandLogger::generate_filename() const
{
  auto t = std::time(nullptr);
  auto tm = *std::localtime(&t);

  std::ostringstream oss;
  oss << std::put_time(&tm, "%d-%m-%Y_%H-%M-%S");
  return oss.str() + ".xml";
}