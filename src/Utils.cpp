#include "Utils.hpp"
#include <algorithm>

bool is_char_underscore(char x)
{
  return (x == '_') || (x >= 'A' && x <= 'Z') || (x >= 'a' && x <= 'z');
}

bool is_num_char_underscore(char x)
{
  return is_char_underscore(x) || (x >= '0' && x <= '9');
}

std::string lowercase(std::string s)
{
  std::transform(s.begin(), s.end(), s.begin(), [](char ch) {
    return (ch >= 'A' && ch <= 'Z' ? ch + 32 : ch);
  });
  return s;
}

std::string remove_whitespace(std::string s)
{
  s.erase(std::remove_if(s.begin(), s.end(),
                         [](char x) { return std::isspace(x); }),
          s.end());
  return s;
}

std::string strip(std::string s)
{
  s.erase(s.begin(),
          std::find_if(s.begin(), s.end(), [](char ch) { return ch != ' '; }));

  s.erase(std::find_if(s.rbegin(), s.rend(), [](char ch) { return ch != ' '; })
              .base(),
          s.end());
  return s;
}