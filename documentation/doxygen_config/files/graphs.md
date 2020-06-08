# Code Overview

## Class Diagram

\image html media/ClassDiagram.png
**Note**: Not all classes, but all self programmed and important classes are pictured above. This diagram should give a overview on the project.

This class diagram presents the classes and namespaces in Complex Number Shell.
It also shows the inheritance and associations.
The main class in the middle is the CLI.
It is responsible for the communication with the user and the processing of input commands.
For dealing with complex numbers the Complex class is used.
This class has the Exponential class as a extension to deal with complex numbers in the exponential form.
Calculations with complex numbers are made with the ComplexShuntingYard class.
On the right are all CLI functions listed.
They all inherit from CliFunc.
These functions can be called via a command in the input of the CLI.
The HelpFunc in addition uses the class widthstream, that is responsible for a formatted output of help docs.
It is capable of giving a help output for all functions or only for a wanted function.