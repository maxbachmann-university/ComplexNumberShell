#pragma once

#include <string>
#include <ostream>

template<typename T>
struct Exponential {
  T r;
  T phi;
  Exponential(T r, T phi)
    : r(r), phi(phi) {}
  std::string str() const;
};

template<class T>
std::string Exponential<T>::str() const {
  if (r == 0) {
    return "0";
  }
  if (phi == 0) {
	  return std::to_string(r);
  }
  return std::to_string(r) + "*e^j" + std::to_string(phi);
}

template<typename T, typename CharT, class Traits>
std::basic_ostream<CharT, Traits>&
operator<<(std::basic_ostream<CharT, Traits>& os, const Exponential<T>& exp_z)
{
  return os << exp_z.str();
}