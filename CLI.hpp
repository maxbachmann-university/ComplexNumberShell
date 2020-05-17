#pragma once
#include "Complex.hpp"
#include <unordered_map>
#include <vector>

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
    std::unordered_map<std::string, Complex<double>> variable_mapping;   

    void assign_result(const std::vector<std::string>& assignments, Complex<double> result);

    std::string remove_whitespace(std::string assignment) const;

    std::vector<std::string> split_assignments(const std::string& assignment) const;
};
