
cmake_minimum_required(VERSION 3.1)
project (ComplexNumberShell)

include_directories(include extern)
add_executable(ComplexNumberShell ComplexNumberShell.cpp src/ComplexShuntingYard.cpp src/CLI.cpp src/CliFuncs/HelpFunc.cpp src/CliParser.cpp src/Utils.cpp src/CliFunc.cpp src/XmlCommandLogger.cpp extern/tinyxml2/tinyxml2.cpp extern/widthstream/widthstream.cpp)
target_compile_features(ComplexNumberShell PRIVATE cxx_std_17)