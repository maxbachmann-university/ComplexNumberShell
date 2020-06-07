#include "XmlCommandLogger.hpp"

#include <ctime>
#include <iomanip>
#include <sstream>

// thread safe version of std::localtime taken from
// https://stackoverflow.com/questions/38034033/c-localtime-this-function-or-variable-may-be-unsafe
inline std::tm localtime_xp(std::time_t timer)
{
    std::tm bt {};
#if defined(__unix__)
    localtime_r(&timer, &bt);
#elif defined(_MSC_VER)
    localtime_s(&bt, &timer);
#else
    static std::mutex mtx;
    std::lock_guard<std::mutex> lock(mtx);
    bt = *std::localtime(&timer);
#endif
    return bt;
}

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
  auto tm = localtime_xp(std::time(nullptr));

  std::ostringstream oss;
  oss << std::put_time(&tm, "%d-%m-%Y_%H-%M-%S");
  return oss.str() + ".xml";
}