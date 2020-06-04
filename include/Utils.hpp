#pragma once
#include <string>

template <class... Ts> struct overload : Ts... {
  using Ts::operator()...;
};
template <class... Ts> overload(Ts...) -> overload<Ts...>;

bool is_char_underscore(char x);

bool is_num_char_underscore(char x);

std::string lowercase(std::string s);

std::string remove_whitespace(std::string s);

std::string strip(std::string s);