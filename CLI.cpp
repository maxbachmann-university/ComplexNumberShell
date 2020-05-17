#include "CLI.hpp"
#include "ComplexShuntingYard.hpp"
#include <iostream>
#include <exception>

CLI::CLI() {
	print_startup();
}

void CLI::print_startup() {
	std::cout
	  << "Welcome to the Complex Number Shell\n"
	  << "type \"help()\", \"credits()\" for more information.\n";
}

void CLI::print_credits() {
	std::cout
	  << "Created by:\n"
	  << "  Bachmann Maximilian\n"
	  << "  Eisenmann Marvin\n"
	  << "  Vetter Florian\n";
}

void CLI::print_help() {
	std::cout
	    << "Help:\n"
		<< "    Calculations:\n"
		<< "       Calculations can use the operators *, /, +, - and brackets to calculate complex numbers\n"
		<< "       For the complex numbers the cartesian form (<a>+<b>i), the euler form (<r>*e^i<phi>), \n"
		<< "       or a variable holding a complex number can be used. It is possible to use j instead of i for complex numbers\n\n"
		<< "       Example:\n"
		<< "           >>> 1+1j\n"
		<< "           (1+1j)\n"
		<< "           >>> (1+1i) + (1 - 1i)\n"
		<< "           (2+0j)\n"
		<< "           >>> a = 1 + 1j\n"
		<< "           >>> (a - 1i) * 4 * (1 - 1i)\n"
		<< "           (4-4j)\n\n"
		
		<< "    Assignments:\n"
		<< "       It is possible to assign the results of calculations to variables\n"
		<< "       Operators (e.g. *) can not be used in variable names\n"
		<< "       It is possible to save a complex number into two variables in the form (a,b)\n"
		<< "       where the real part is stored in a and the imaginary part in b\n\n"
		<< "       Example:\n"
		<< "           >>> example_var1 = real, complex = 1+1j\n"
		<< "           >>> example_var1\n"
		<< "           (1+1j)\n"
		<< "           >>> real\n"
		<< "           (1+0j)\n"
		<< "           >>> complex\n"
		<< "           1j\n\n"

		<< "    Commands:\n"
		<< "       These commands can be used inside expressions\n\n"
		<< "       Example:\n"
		<< "           >>> 2*abs(1+1i)\n"
		<< "           (2.828428+0.000000j)\n\n"

        << "       abs(<complex number>\n"
        << "          Return magnitude\n"
        << "       arg(<complex number>\n"
        << "          Return phase angle\n"
        << "       norm(<complex number>\n"
        << "          Return squared magnitude (field norm)\n"
        << "       conj(<complex number>\n"
        << "          Return Complex conjugate\n"
        << "       cos(<complex number>\n"
        << "          Return Complex cosine\n"
        << "       cosh(<complex number>\n"
        << "          Return Complex hyperbolic cosine\n"
        << "       exp(<complex number>\n"
        << "          Return Complex base e exponential\n"
        << "       log(<complex number>\n"
        << "          Return Complex natural logarithm\n"
        << "       log10(<complex number>\n"
        << "          Return Complex base 10 logarithm\n"
        << "       sin(<complex number>\n"
        << "          Return Complex sine\n"
        << "       sinh(<complex number>\n"
        << "          Return Complex hyperbolic sine\n"
        << "       sqrt(<complex number>\n"
        << "          Return Complex square root\n"
        << "       tan(<complex number>\n"
        << "          Return Complex tangent\n"
        << "       tanh(<complex number>\n"
        << "          Return Complex hyperbolic tangent\n\n"
		<< "    Global commands:\n"
		<< "       These commands can not be used inside expressions\n\n"
		<< "       euler_print(<complex number>)\n"
		<< "          print complex number in euler form\n"
		<< "       cartesian_print(<complex number>)\n"
		<< "          print complex number in cartesian form\n"
		<< "       quit()/exit()\n"
		<< "          leave the application\n"
		<< "       help()\n"
		<< "          output this help text\n";
}

void CLI::evaluate_command() {
	if (current_command == "quit()" || current_command == "exit()") {
		exit(EXIT_SUCCESS);
    } else if (current_command == "credits()") {
		print_credits();
    } else if (current_command == "help()") {
		print_help();
    } else if (current_command.rfind("euler_print(", 0) == 0 && current_command.back() == ')') {
		std::string command = current_command.substr(12, current_command.length()-13);
		if (command.find('=') != std::string::npos) {
            throw std::invalid_argument("SyntaxError: Can not use assignment inside function call");
		}
		ComplexShuntingYard calc(command, variable_mapping);
		auto result = calc.evaluate();
		std::cout << result.to_exponential() << "\n";
    } else if (current_command.rfind("cartesian_print(", 0) == 0 && current_command.back() == ')') {
	    std::string command = current_command.substr(16, current_command.length()-17);
		if (command.find('=') != std::string::npos) {
            throw std::invalid_argument("SyntaxError: Can not use assignment inside function call");
		}
		ComplexShuntingYard calc(command, variable_mapping);
		auto result = calc.evaluate();
		std::cout << result << "\n";
    } else {
       	std::vector<std::string> assignments = split_assignments(current_command);
	    std::string command = assignments.back();
	    assignments.pop_back();

		ComplexShuntingYard calc(command, variable_mapping);
		auto result = calc.evaluate();
		if (assignments.empty()) {
		    std::cout << result << "\n";
	    } else {
			assign_result(assignments, result);
		}
	}
}

void CLI::read_new_command() {
	std::cout << ">>> ";
	std::string command;
	std::getline(std::cin, command);
	// removing whitespace in assignment should not happen!!!
	current_command = remove_whitespace(std::move(command));
}

void CLI::assign_result(const std::vector<std::string>& assignments, Complex<double> result) {
    for (const auto& assignment : assignments) {
		if (assignment[0] >= '0' && assignment[0] <= '9') {
			if (assignment.length() == 1) {
				throw std::invalid_argument("SyntaxError: can't assign to literal");
			}
			throw std::invalid_argument("SyntaxError: invalid syntax");
		}
	    std::size_t comma_pos = 0;
	    for (std::size_t i = 0; i<assignment.length(); ++i) {
			const char ch = assignment[i];
			if (ch == '+' || ch == '-' || ch == '*' || ch == '/') {
				throw std::invalid_argument("SyntaxError: can't assign to operator");
			}
			if (ch == ',') {
				if (i == 0) {
					throw std::invalid_argument("SyntaxError: Invalid syntax");
				}
				if (comma_pos) {
					throw std::invalid_argument("SyntaxError: can only unpack complex to 1 or 2 variables");
				}
				comma_pos = i;
			}
		}

		if (comma_pos) {
			variable_mapping[assignment.substr(0, comma_pos)] = real(result);
			variable_mapping[assignment.substr(comma_pos+1)] = Complex<double>(0, imag(result));

		} else {
            variable_mapping[assignment] = result;
		}
	}
}

std::string CLI::remove_whitespace(std::string assignment) const {
	assignment.erase(
	    std::remove_if(assignment.begin(), assignment.end(), [](char x){ return std::isspace(x); }),
	    assignment.end());
	return assignment;
}

std::vector<std::string> CLI::split_assignments(const std::string& assignment) const {
    std::vector<std::string> output;

    auto first = assignment.data(), second = assignment.data(), last = first + assignment.size();
    for (; second != last && first != last; first = second + 1) {
        second = std::find_if(first, last, [](const char& ch) {
            return ch == '=';
        });
    
        if (first != second) {
            output.emplace_back(first, second - first);
        }
    }

    return output;
}
