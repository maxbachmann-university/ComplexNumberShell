// Interface inspired by the standard library https://en.cppreference.com/w/cpp/numeric/complex
#pragma once

#include "Exponential.hpp"

#include <cmath>
#include <algorithm>
#include <ostream>

// Forward declarations.
template<typename T> struct Complex;

template<typename T> constexpr T real(const Complex<T>& z);

template<typename T> constexpr T imag(const Complex<T>& z);

template<typename T> constexpr T real(const T& z);

template<typename T> constexpr T imag(const T&);

///  Return magnitude.
template<typename T> T abs(const Complex<T>&);
///  Return phase angle.
template<typename T> T arg(const Complex<T>&);
///  Return squared magnitude (field norm)
template<typename T> T norm(const Complex<T>&);
///  Return Complex conjugate.
template<typename T> Complex<T> conj(const Complex<T>&);
///  Return Complex with magnitude rho and angle theta.
template<typename T> Complex<T> polar(const T&, const T& = T());

/// Return Complex cosine.
template<typename T> Complex<T> cos(const Complex<T>&);
/// Return Complex hyperbolic cosine.
template<typename T> Complex<T> cosh(const Complex<T>&);
/// Return Complex base e exponential.
template<typename T> Complex<T> exp(const Complex<T>&);
/// Return Complex natural logarithm.
template<typename T> Complex<T> log(const Complex<T>&);
/// Return Complex base 10 logarithm.
template<typename T> Complex<T> log10(const Complex<T>&);
/// Return Tx to the y'th power.
template<typename T> Complex<T> pow(const Complex<T>&, const T&);
/// Return Tx to the y'th power.
template<typename T> Complex<T> pow(const Complex<T>&, const Complex<T>&);
/// Return Tx to the y'th power.
template<typename T> Complex<T> pow(const T&, const Complex<T>&);
/// Return Complex sine.
template<typename T> Complex<T> sin(const Complex<T>&);
/// Return Complex hyperbolic sine.
template<typename T> Complex<T> sinh(const Complex<T>&);
/// Return Complex square root.
template<typename T> Complex<T> sqrt(const Complex<T>&);
/// Return Complex tangent.
template<typename T> Complex<T> tan(const Complex<T>&);
/// Return Complex hyperbolic tangent.
template<typename T> Complex<T> tanh(const Complex<T>&);

template<typename T>
struct Complex
{
  constexpr Complex(const T& real = T(), const T& imag = T())
    : m_real(real), m_imag(imag) { }

  constexpr Complex(const Complex&) = default;

  template<typename U>
  constexpr Complex(const Complex<U>& z)
      : m_real(z.real()), m_imag(z.imag()) { }

  Complex<T>& operator=(const T&);

  Complex& operator=(const Complex&) = default;

  constexpr T real() const { return m_real; }
  constexpr T imag() const { return m_imag; }

  void real(T val) { m_real = val; }
  void imag(T val) { m_imag = val; }

  Complex<T>& operator+=(const T&);

  template<typename U>
  Complex<T>& operator+=(const Complex<U>&);

  Complex<T>& operator-=(const T&);

  template<typename U>
  Complex<T>& operator-=(const Complex<U>&);

  Complex<T>& operator*=(const T&);

  template<typename U>
  Complex<T>& operator*=(const Complex<U>&);

  Complex<T>& operator/=(const T&);

  template<typename U>
  Complex<T>& operator/=(const Complex<U>&);

  static Complex<T> from_exponential(const Exponential<T>&);

  Exponential<T> to_exponential() const;

  std::string str() const;

private:
  T m_real;
  T m_imag;
};


#include "Complex.txx"