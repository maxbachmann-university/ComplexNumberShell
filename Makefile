cpp_files = src/ComplexShuntingYard.cpp src/CLI.cpp src/widthstream.cpp src/CliFuncs/HelpFunc.cpp src/CliParser.cpp src/Utils.cpp src/CliFunc.cpp src/XmlCommandLogger.cpp extern/tinyxml2/tinyxml2.cpp
include_dirs = -I include -I extern

compile:
	g++ main.cpp $(cpp_files) $(include_dirs) -o ComplexNumberShell -std=c++17