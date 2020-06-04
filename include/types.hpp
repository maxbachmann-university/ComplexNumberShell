#pragma once

#include <string>
#include <vector>
#include <unordered_map>
#include <variant>
#include "Complex.hpp"

using arg_list = std::vector<std::string>;
using var_mapping = std::unordered_map<std::string, Complex<double>>;
using call_result = std::variant<std::monostate, Complex<double>>;