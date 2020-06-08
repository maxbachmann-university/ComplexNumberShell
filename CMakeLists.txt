
cmake_minimum_required(VERSION 3.1)
project (ComplexNumberShell)
set(CMAKE_CXX_STANDARD 17)

include_directories(include extern)
add_executable(ComplexNumberShell ComplexNumberShell.cpp src/ComplexShuntingYard.cpp src/CLI.cpp src/CliFuncs/HelpFunc.cpp src/CliParser.cpp src/Utils.cpp src/CliFunc.cpp src/XmlCommandLogger.cpp extern/tinyxml2/tinyxml2.cpp extern/widthstream/widthstream.cpp)

add_library(catch2_lib OBJECT
    tests/mainTesting.cpp
)

add_executable(TestComplexShuntingYard tests/TestComplexShuntingYard.cpp src/ComplexShuntingYard.cpp)
target_link_libraries(TestComplexShuntingYard catch2_lib)