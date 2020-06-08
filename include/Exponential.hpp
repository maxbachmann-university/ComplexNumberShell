#pragma once

#include <ostream>
#include <string>

/**
 * @brief Datastructure holding a complex numbers in euler form
 */
template <typename T>
struct Exponential {
  T r;
  T phi;
  Exponential(T r, T phi) : r(r), phi(phi)
  {}
  std::string str() const;
};

/**
 * Get string representation of exponential complex number.
 */
template <typename T>
std::string Exponential<T>::str() const
{
  if (r == 0) {
    return "0";
  }
  if (phi == 0) {
    return std::to_string(r);
  }
  return std::to_string(r) + "*e^j" + std::to_string(phi);
}

/**
 * Add the euler form of a complex number to an output stream.
 */
template <typename T, typename CharT, typename Traits>
std::basic_ostream<CharT, Traits>&
operator<<(std::basic_ostream<CharT, Traits>& os, const Exponential<T>& exp_z)
{
  return os << exp_z.str();
}