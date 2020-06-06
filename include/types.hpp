#pragma once

#include "Complex.hpp"
#include <string>
#include <unordered_map>
#include <variant>
#include <vector>

using arg_list = std::vector<std::string>;
using var_mapping = std::unordered_map<std::string, Complex<double>>;
using call_result = std::variant<std::monostate, Complex<double>>;