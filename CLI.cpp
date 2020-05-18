#include "CLI.hpp"
#include "ComplexShuntingYard.hpp"
#include <iostream>
#include <exception>
#include <regex>

template<class... Ts> struct overload : Ts... { using Ts::operator()...; };
template<class... Ts> overload(Ts...) -> overload<Ts...>;


CLI::CLI() {
    print_startup();
}

void CLI::evaluate_command() {
    if (tokens.empty()) {
        return;
    }
    std::vector<std::string> assignments = split_assignments(tokens);
    tokens = assignments.back();
    assignments.pop_back();

    subsitute_variables();

    std::vector<std::pair<std::string, std::string>> method_calls;
    do {
        method_calls = find_inner_method_calls();
        for (const auto& method_call : method_calls) {
            // inner is always a calculation since find_inner_method_calls
            // finds the most inner function calls
            Complex<double> inner_val = 0;
            if (!method_call.second.empty()) {
                inner_val = ComplexShuntingYard::evaluate(method_call.second);
             }
            auto result = call_func_by_name(method_call.first, inner_val);

            std::string full_match = method_call.first + "(" + method_call.second + ")";
            size_t start_pos = tokens.find(full_match);

            if (result.index() == 0) {
                if (!assignments.empty()) {
                    throw std::invalid_argument("SyntaxError: can't assign None Type");
                }
                return;
            }
            std::string replacement = std::get<1>(result).str();

            tokens.replace(start_pos, full_match.length(), replacement);
        }
    } while (!method_calls.empty());

    Complex<double> result = ComplexShuntingYard::evaluate(tokens);
    assign_result(assignments, result);
}

void CLI::subsitute_variables() {
    // execute twice to catch all variables e.g. a*a -> (<complex>)*a -> (<complex>)*(<complex>)
    for (int i = 0; i<2; ++i) {
        std::regex variable_regex(R"(([\(\*\/\+\-]|^)([^\d\^\(\)\+\*\/\-][^\^\(\)\+\*\/\-]*)([\)\*\/\+\-]|$))");
        auto variable_begin = std::sregex_iterator(tokens.begin(), tokens.end(), variable_regex);
        auto variable_end = std::sregex_iterator();
        std::vector<std::pair<std::string, std::size_t>> matches;

        for (std::sregex_iterator i = variable_begin; i != variable_end; ++i) {
            std::smatch match = *i;
            matches.emplace_back(match[2].str(), match.position(2));
        }

        signed int pos_change = 0;
        for (const auto& match : matches) {
            if (variable_mapping.count(match.first) == 0) {
                throw std::invalid_argument("NameError: name '" + match.first + "' is not defined");
            }

            std::string replacement = variable_mapping.at(match.first).str();
            tokens.replace(match.second+pos_change, match.first.length(), replacement);
            pos_change += replacement.length() - match.first.length();
        }
    }
}

std::vector<std::pair<std::string, std::string>> CLI::find_inner_method_calls() {
    std::regex variable_regex(R"([^\s\d\(\)\+\*\/\-][^\s\(\)\+\*\/\-]*\([ij\.\d\+\*\-\+\(\)]*\))");
    auto variable_begin = std::sregex_iterator(tokens.begin(), tokens.end(), variable_regex);
    auto variable_end = std::sregex_iterator();
    std::vector<std::string> matches;

    for (std::sregex_iterator i = variable_begin; i != variable_end; ++i) {
        std::smatch match = *i;
        std::string match_str = match.str();
        matches.push_back(match_str);
    }
    std::vector<std::pair<std::string, std::string>> ops;
    for (auto match : matches) {
        auto found=match.find("(");
        std::string op = match.substr(0, found);
        std::size_t brackets = 1;
        std::size_t bracket_end = found+1;
        for (; bracket_end < match.length() && brackets != 0; ++bracket_end) {
            if (match[bracket_end] == ')') {
                brackets -= 1;
            } else if (match[bracket_end] == '(') {
                brackets += 1;
            }
        }
        if (brackets != 0) {
            throw std::invalid_argument("Calculation failed: mismatched parentheses");
        }

        match = match.substr(0, bracket_end);
        std::string calc = match.substr(found+1, bracket_end-found-2);
        ops.emplace_back(op, calc);
    }

    return ops;
}

void CLI::read_new_command() {
    std::cout << ">>> ";
    std::string command;
    std::getline(std::cin, command);
    // removing whitespace in assignment should not happen!!!
    current_command = remove_whitespace(std::move(command));
    tokens = current_command;
}


void CLI::assign_result(const std::vector<std::string>& assignments, Complex<double> result)
{
    if (assignments.empty()) {
        std::cout << result.str() << "\n";
        return;
    }

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

std::variant<std::monostate, Complex<double>>
CLI::call_func_by_name(std::string func_name, Complex<double> a){
    if (func_name == "abs") return abs(a);
    if (func_name == "arg") return arg(a);
    if (func_name == "norm") return norm(a);
    if (func_name == "conj") return conj(a);
    if (func_name == "cos") return cos(a);
    if (func_name == "cosh") return cosh(a);
    if (func_name == "sin") return sin(a);
    if (func_name == "sinh") return sinh(a);
    if (func_name == "tan") return tan(a);
    if (func_name == "tanh") return tanh(a);
    if (func_name == "exp") return exp(a);
    if (func_name == "log") return log(a);
    if (func_name == "log10") return log10(a);
    if (func_name == "sqrt") return sqrt(a);
    if (func_name == "real") return real(a);
    if (func_name == "imag") return imag(a);
    if (func_name == "help") {
        print_help();
        return {};
    }
    if (func_name == "credits") {
        print_credits();
        return {};
    }
    if (func_name == "euler_print") {
        std::cout << a.to_exponential() << "\n";
        return {};
    }
    if (func_name == "print" || func_name == "cartesian_print") {
        std::cout << a << "\n";
        return {};
    }
    if (func_name == "quit" || func_name == "exit") exit(EXIT_SUCCESS);
    throw std::invalid_argument("NameError: name '" + func_name + "' is not defined");
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
    std::cout << R"(Help:
    Calculations:
        Calculations can use the operators *, /, +, - and brackets to calculate complex numbers
        For the complex numbers the cartesian form (<a>+<b>i), the euler form (<r>*e^i<phi>),
        or a variable holding a complex number can be used. It is possible to use j instead of i for complex numbers

        Example:
            >>> 1+1j
            (1+1j)
            >>> (1+1i) + (1 - 1i)
            (2+0j)
            >>> a = 1 + 1j
            >>> (a - 1i) * 4 * (1 - 1i)
            (4-4j)

        Assignments:
            It is possible to assign the results of calculations to variables
            Operators (e.g. *) can not be used in variable names
            It is possible to save a complex number into two variables in the form (a,b)
            where the real part is stored in a and the imaginary part in b
            Example:
                >>> example_var1 = real, complex = 1+1j
                >>> example_var1
                (1+1j)
                >>> real
                (1+0j)
                >>> complex
                1j

        Commands:
            These commands can be used inside expressions

            Example:
                >>> real(2 + 1i) * abs(1+1i)
                (2.828428+0.000000j)

            real(<complex number>
                Return real component of the complex number
            imag(<complex number>
                Return imaginary component of the complex number
            abs(<complex number>
                Return magnitude
            arg(<complex number>
                Return phase angle
            norm(<complex number>
                Return squared magnitude (field norm)
            conj(<complex number>
                Return Complex conjugate
            cos(<complex number>
                Return Complex cosine
            cosh(<complex number>
                Return Complex hyperbolic cosine
            exp(<complex number>
                Return Complex base e exponential
            log(<complex number>
                Return Complex natural logarithm
            log10(<complex number>
                Return Complex base 10 logarithm
            sin(<complex number>
                Return Complex sine
            sinh(<complex number>
                Return Complex hyperbolic sine
            sqrt(<complex number>
                Return Complex square root
            tan(<complex number>
                Return Complex tangent
            tanh(<complex number>
                Return Complex hyperbolic tangent

        Global commands:
            These commands can not be used inside expressions

            euler_print(<complex number>)
                print complex number in euler form
            print(<complex number>)/cartesian_print(<complex number>)
                print complex number in cartesian form
            quit()/exit()
                leave the application
            help()
                output this help text
)";
}
