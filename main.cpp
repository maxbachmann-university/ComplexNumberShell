#include "CLI.hpp"
#include <iostream>
#include <exception>

int main() {
    CLI cli;
    while (true) {
        try {
            cli.read_new_command();
            cli.evaluate_command();
        } catch(const std::exception& e) {
            std::cout << e.what() << "\n";
        }
    }
    return 0;
}  