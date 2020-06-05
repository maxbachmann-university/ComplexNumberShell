// Interface inspired by the standard library
// https://en.cppreference.com/w/cpp/numeric/complex
#pragma once

#include "Exponential.hpp"

#include <algorithm>
#include <cmath>
#include <ostream>

// Forward declarations.
template <typename T> struct Complex;

/**
 * Return real part.
 */
template <typename T> constexpr T real(const Complex<T>& z);

/**
 * Return imaginary part.
 */
template <typename T> constexpr T imag(const Complex<T>& z);

/**
 * Return real part.
 */
template <typename T> constexpr T real(const T& z);

/**
 * Return imaginary part.
 */
template <typename T> constexpr T imag(const T&);

/**
 * Return magnitude.
 */
template <typename T> T abs(const Complex<T>&);

/**
 * Return phase angle.
 */
template <typename T> T arg(const Complex<T>&);
 
/**
 * Return squared magnitude (field norm).
 */
template <typename T> T norm(const Complex<T>&);

/**
 * Return Complex conjugate.
 */
template <typename T> Complex<T> conj(const Complex<T>&);
  
/**
 * Return Complex with magnitude rho and angle theta.
 */
template <typename T> Complex<T> polar(const T&, const T& = T());


/**
 * Return Complex cosine.
 */
template <typename T> Complex<T> cos(const Complex<T>&);

/**
 * Return Complex hyperbolic cosine.
 */
template <typename T> Complex<T> cosh(const Complex<T>&);

/**
 * Return Complex base e exponential.
 */
template <typename T> Complex<T> exp(const Complex<T>&);

/**
 * Return Complex natural logarithm.
 */
template <typename T> Complex<T> log(const Complex<T>&);

/**
 * Return Complex base 10 logarithm.
 */
template <typename T> Complex<T> log10(const Complex<T>&);

/**
 * Return Tx to the y'th power.
 */
template <typename T> Complex<T> pow(const Complex<T>&, const T&);

/**
 * Return Tx to the y'th power.
 */
template <typename T> Complex<T> pow(const Complex<T>&, const Complex<T>&);

/**
 * Return Tx to the y'th power.
 */
template <typename T> Complex<T> pow(const T&, const Complex<T>&);

/**
 * Return Complex sine.
 */
template <typename T> Complex<T> sin(const Complex<T>&);

/**
 * Return Complex hyperbolic sine.
 */
template <typename T> Complex<T> sinh(const Complex<T>&);

/**
 * Return Complex square root.
 */
template <typename T> Complex<T> sqrt(const Complex<T>&);

/**
 * Return Complex tangent.
 */
template <typename T> Complex<T> tan(const Complex<T>&);

/**
 * Return Complex hyperbolic tangent.
 */
template <typename T> Complex<T> tanh(const Complex<T>&);

/**
 * Overload "+" operator for using with complex numbers.
 */
template <typename T> Complex<T> operator+(const Complex<T>& lhs, const Complex<T>& rhs);

/**
 * Overload "+" operator for using with complex numbers.
 */
template <typename T> Complex<T> operator+(const Complex<T>& lhs, const T& rhs);

/**
 * Overload "+" operator for using with complex numbers.
 */
template <typename T> Complex<T> operator+(const T& lhs, const Complex<T>& rhs);

/**
 * Overload "+" operator for using with complex numbers.
 */
template <typename T> inline Complex<T> operator+(const Complex<T>& rhs);

/**
 * Overload "-" operator for using with complex numbers.
 */
template <typename T> Complex<T> operator-(const Complex<T>& lhs, const Complex<T>& rhs);

/**
 * Overload "-" operator for using with complex numbers.
 */
template <typename T> Complex<T> operator-(const Complex<T>& lhs, const T& rhs);

/**
 * Overload "-" operator for using with complex numbers.
 */
template <typename T> Complex<T> operator-(const T& lhs, const Complex<T>& rhs);

/**
 * Overload "-" operator for using with complex numbers.
 */
template <typename T> Complex<T> operator-(const Complex<T>& rhs);

/**
 * Overload "*" operator for using with complex numbers.
 */
template <typename T> Complex<T> operator*(const Complex<T>& lhs, const Complex<T>& rhs);

/**
 * Overload "*" operator for using with complex numbers.
 */
template <typename T> Complex<T> operator*(const Complex<T>& lhs, const T& rhs);

/**
 * Overload "*" operator for using with complex numbers.
 */
template <typename T> Complex<T> operator*(const T& lhs, const Complex<T>& rhs);

/**
 * Overload "/" operator for using with complex numbers.
 */
template <typename T> Complex<T> operator/(const Complex<T>& lhs, const Complex<T>& rhs);

/**
 * Overload "/" operator for using with complex numbers.
 */
template <typename T> Complex<T> operator/(const Complex<T>& lhs, const T& rhs);

/**
 * Overload "/" operator for using with complex numbers.
 */
template <typename T> Complex<T> operator/(const T& lhs, const Complex<T>& rhs);

/**
 * Overload "==" operator for using with complex numbers.
 */
template <typename T> constexpr bool operator==(const Complex<T>& lhs, const Complex<T>& rhs);

/**
 * Overload "==" operator for using with complex numbers.
 */
template <typename T> constexpr bool operator==(const Complex<T>& lhs, const T& rhs);

/**
 * Overload "==" operator for using with complex numbers.
 */
template <typename T> constexpr bool operator==(const T& lhs, const Complex<T>& rhs);

/**
 * Overload "!=" operator for using with complex numbers.
 */
template <typename T> constexpr bool operator!=(const Complex<T>& lhs, const Complex<T>& rhs);

/**
 * Overload "!=" operator for using with complex numbers.
 */
template <typename T> constexpr bool operator!=(const Complex<T>& lhs, const T& rhs);

/**
 * Overload "!=" operator for using with complex numbers.
 */
template <typename T> constexpr bool operator!=(const T& lhs, const Complex<T>& rhs);

/**
 * Overloading "<<" operator.
 * 
 * Adds an cartesian complex number to an output stream.
 */
template <typename T, typename CharT, typename Traits>
std::basic_ostream<CharT, Traits>&
operator<<(std::basic_ostream<CharT, Traits>& os, const Complex<T>& z);


/**
 * @brief Struct for calculation with cartesian complex numbers.
 */
template <typename T> struct Complex {
  constexpr Complex(const T& real = T(), const T& imag = T())
      : m_real(real), m_imag(imag)
  {}

  constexpr Complex(const Complex&) = default;

  template <typename U>
  constexpr Complex(const Complex<U>& z) : m_real(z.real()), m_imag(z.imag())
  {}

  /**
  * Overload "=" operator for using with complex numbers.
  */
  Complex<T>& operator=(const T&);

  /**
  * Overload "=" operator for using with complex numbers.
  */
  Complex& operator=(const Complex&) = default;

  /**
  * Return real part.
  */
  constexpr T real() const
  {
    return m_real;
  }

  /**
  * Return imaginary part.
  */
  constexpr T imag() const
  {
    return m_imag;
  }

  /**
  * Set real part.
  */
  void real(T val)
  {
    m_real = val;
  }

  /**
  * Set imaginary part.
  */
  void imag(T val)
  {
    m_imag = val;
  }

  /**
  * Overload "+=" operator for using with complex numbers.
  */
  Complex<T>& operator+=(const T&);

  /**
  * Overload "+=" operator for using with complex numbers.
  */
  template <typename U> Complex<T>& operator+=(const Complex<U>&);

  /**
  * Overload "-=" operator for using with complex numbers.
  */
  Complex<T>& operator-=(const T&);

  /**
  * Overload "-=" operator for using with complex numbers.
  */
  template <typename U> Complex<T>& operator-=(const Complex<U>&);

  /**
  * Overload "*=" operator for using with complex numbers.
  */
  Complex<T>& operator*=(const T&);

  /**
  * Overload "*=" operator for using with complex numbers.
  */
  template <typename U> Complex<T>& operator*=(const Complex<U>&);

  /**
  * Overload "/=" operator for using with complex numbers.
  */
  Complex<T>& operator/=(const T&);

  /**
  * Overload "/=" operator for using with complex numbers.
  */
  template <typename U> Complex<T>& operator/=(const Complex<U>&);

  /**
  * Convert complex number from exponential to cartesian.
  */
  static Complex<T> from_exponential(const Exponential<T>&);

  /**
  * Convert complex number from cartesian to exponential.
  */
  Exponential<T> to_exponential() const;

  /**
  * Get string representation of cartesian complex number.
  */
  std::string str() const;

private:
  T m_real;
  T m_imag;
};

#include "Complex.txx"