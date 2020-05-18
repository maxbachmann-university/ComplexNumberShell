#pragma once
#include "Complex.hpp"
#include <unordered_map>
#include <vector>
#include <variant>

class CLI {
public:
    CLI();

    void print_startup();
    void print_credits();
    void print_help();
    void evaluate_command();
    void read_new_command();
private:
    std::string current_command;
    std::string tokens;

    std::unordered_map<std::string, Complex<double>> variable_mapping;

    std::variant<std::monostate, Complex<double>>
    call_func_by_name(std::string func_name, Complex<double> a = 0);

    void subsitute_variables();

    void assign_result(const std::vector<std::string>& assignments, Complex<double> result);

    std::vector<std::pair<std::string, std::string>> find_inner_method_calls();

    std::string remove_whitespace(std::string assignment) const;

    std::vector<std::string> split_assignments(const std::string& assignment) const;
};
