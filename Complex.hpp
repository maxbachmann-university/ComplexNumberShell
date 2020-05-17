// Interface taken from https://en.cppreference.com/w/cpp/numeric/complex
#pragma once

#include <cmath>
#include <algorithm>
#include <ostream>

// Forward declarations.
template<typename T> struct Complex;

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
/// Return Complex inverse cosine.
template<typename T> Complex<T> acos(const Complex<T>&);
/// Return Complex inverse sine.
template<typename T> Complex<T> asin(const Complex<T>&);
/// Return Complex inverse tangent.
template<typename T> Complex<T> atan(const Complex<T>&);
/// Return Complex inverse hyperbolic cosine.
template<typename T> Complex<T> acosh(const Complex<T>&);
/// Return Complex inverse hyperbolic sine.
template<typename T> Complex<T> asinh(const Complex<T>&);
/// Return Complex inverse hyperbolic tangent.
template<typename T> Complex<T> atanh(const Complex<T>&);

template<typename T>
struct Exponential {
  T r;
  T phi;
  Exponential(T r, T phi)
    : r(r), phi(phi) {}
};


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

private:
  T m_real;
  T m_imag;
};

template<typename T>
Complex<T>& Complex<T>::operator=(const T& rhs) {
  m_real = rhs;
  m_imag = T();
  return *this;
}

template<typename T>
Complex<T>& Complex<T>::operator+=(const T& rhs) {
  m_real += rhs;
	return *this;
}

template<typename T>
Complex<T>& Complex<T>::operator-=(const T& rhs) {
  m_real -= rhs;
  return *this;
}

template<typename T>
Complex<T>& Complex<T>::operator*=(const T& rhs)
{
  m_real *= rhs;
  m_imag *= rhs;
  return *this;
}

template<typename T>
Complex<T>& Complex<T>::operator/=(const T& rhs)
{
  m_real /= rhs;
  m_imag /= rhs;
  return *this;
}

template<typename T>
template<typename U>
Complex<T>& Complex<T>::operator+=(const Complex<U>& rhs)
{
  m_real += rhs.real();
  m_imag += rhs.imag();
  return *this;
}

template<typename T>
template<typename U>
Complex<T>& Complex<T>::operator-=(const Complex<U>& rhs)
{
  m_real -= rhs.real();
  m_imag -= rhs.imag();
  return *this;
}

template<typename T>
template<typename U>
Complex<T>& Complex<T>::operator*=(const Complex<U>& rhs)
{
  const T temp = m_real * rhs.real() - m_imag * rhs.imag();
  m_imag = m_real * rhs.imag() + m_imag * rhs.real();
  m_real = temp;
  return *this;
}

template<typename T>
template<typename U>
Complex<T>& Complex<T>::operator/=(const Complex<U>& rhs)
{
  const T _norm = norm(rhs);
  const T temp = (m_real * rhs.real() + m_imag * rhs.imag()) / _norm;
  m_imag = (m_imag * rhs.real() - m_real * rhs.imag()) / _norm;
  m_real = temp;
  return *this;
}

template<typename T>
inline Complex<T> operator+(const Complex<T>& lhs, const Complex<T>& rhs)
{
  Complex<T> result = lhs;
  result += rhs;
  return result;
}

template<typename T>
inline Complex<T> operator+(const Complex<T>& lhs, const T& rhs)
{
  Complex<T> result = lhs;
  result += rhs;
  return result;
}

template<typename T>
inline Complex<T> operator+(const T& lhs, const Complex<T>& rhs)
{
  return rhs + lhs;
}

template<typename T>
inline Complex<T> operator+(const Complex<T>& rhs)
{
	return rhs;
}


template<typename T>
inline Complex<T> operator-(const Complex<T>& lhs, const Complex<T>& rhs)
{
  Complex<T> result = lhs;
  result -= rhs;
  return result;
}

template<typename T>
inline Complex<T> operator-(const Complex<T>& lhs, const T& rhs)
{
  Complex<T> result = lhs;
  result -= rhs;
  return result;
}

template<typename T>
inline Complex<T> operator-(const T& lhs, const Complex<T>& rhs)
{
  Complex<T> result = lhs;
  result -= rhs;
  return result;
}

template<typename T>
inline Complex<T> operator-(const Complex<T>& rhs)
{
	return {-rhs.real(), -rhs.imag()};
}

template<typename T>
inline Complex<T> operator*(const Complex<T>& lhs, const Complex<T>& rhs)
{
  Complex<T> result = lhs;
  result *= rhs;
  return result;
}

template<typename T>
inline Complex<T> operator*(const Complex<T>& lhs, const T& rhs)
{
  Complex<T> result = lhs;
  result *= rhs;
  return result;
}

template<typename T>
inline Complex<T> operator*(const T& lhs, const Complex<T>& rhs)
{
  return rhs * lhs;
}

template<typename T>
inline Complex<T> operator/(const Complex<T>& lhs, const Complex<T>& rhs)
{
  Complex<T> result = lhs;
  result /= rhs;
  return result;
}

template<typename T>
inline Complex<T> operator/(const Complex<T>& lhs, const T& rhs)
{
  Complex<T> result = lhs;
  result /= rhs;
  return result;
}

template<typename T>
inline Complex<T> operator/(const T& lhs, const Complex<T>& rhs)
{
  return rhs / lhs;
}

template<typename T>
inline constexpr bool operator==(const Complex<T>& lhs, const Complex<T>& rhs)
{
  return lhs.real() == rhs.real() && lhs.imag() == rhs.imag();
}

template<typename T>
inline constexpr bool operator==(const Complex<T>& lhs, const T& rhs)
{
  return lhs.real() == rhs && lhs.imag() == 0;
}

template<typename T>
inline constexpr bool operator==(const T& lhs, const Complex<T>& rhs)
{
  return rhs == lhs;
}

template<typename T>
inline constexpr bool operator!=(const Complex<T>& lhs, const Complex<T>& rhs)
{
  return !(lhs == rhs);
}

template<typename T>
inline constexpr bool operator!=(const Complex<T>& lhs, const T& rhs)
{
  return !(lhs == rhs);
}

template<typename T>
inline constexpr bool operator!=(const T& lhs, const Complex<T>& rhs)
{
  return !(lhs == rhs);
}

template<typename T, typename CharT, class Traits>
std::basic_ostream<CharT, Traits>&
operator<<(std::basic_ostream<CharT, Traits>& os, const Complex<T>& z)
{
  if (z.real() == 0) {
    return os << z.imag() << "j";
  } else if (z.imag() >= 0) {
    return os << "(" << z.real() << "+" << z.imag() << "j)";
  } else {
    return os << "(" << z.real() << z.imag() << "j)";
  }
}

template<typename T, typename CharT, class Traits>
std::basic_ostream<CharT, Traits>&
operator<<(std::basic_ostream<CharT, Traits>& os, const Exponential<T>& exp_z)
{
  if (exp_z.r == 0) {
    return os << 0;
  }
  return os << exp_z.r << "*e^j" << exp_z.phi;
}

/*************************/
/*      Utilities        */
/*************************/

template<typename T>
constexpr T real(const Complex<T>& z)
{
  return z.real();
}

template<typename T>
constexpr T imag(const Complex<T>& z)
{
  return z.imag();
}

template<typename T>
constexpr T real(const T& z)
{
  return z;
}

template<typename T>
constexpr T imag(const T&)
{
  return T();
}

template<typename T>
inline T abs(const Complex<T>& z)
{
  return std::sqrt(std::pow(z.real(), 2) + std::pow(z.imag(), 2));
}

template<typename T>
inline T arg(const Complex<T>& z)
{
  return std::atan2(z.imag(), z.real());
}

template<typename T>
inline T norm(const Complex<T>& z)
{
  return std::pow(z.real(), 2) + std::pow(z.imag(), 2);
}

template<typename T>
inline Complex<T> polar(const T& rho, const T& theta)
{
  return Complex<T>(rho * std::cos(theta), rho * std::sin(theta));
}

template<typename T>
inline Complex<T> conj(const Complex<T>& z)
{
  return Complex<T>(z.real(), -z.imag());
}

template<typename T>
inline Complex<T> cos(const Complex<T>& z)
{
  const T _real = z.real();
  const T _imag = z.imag();
  return Complex<T>(std::cos(_real) * std::cosh(_imag), -std::sin(_real) * std::sinh(_imag));
}

template<typename T>
inline Complex<T> cosh(const Complex<T>& z)
{
  const T _real = z.real();
  const T _imag = z.imag();
  return Complex<T>(std::cosh(_real) * std::cos(_imag), std::sinh(_real) * std::sin(_imag));
}

template<typename T>
inline Complex<T> exp(const Complex<T>& z)
{
  return polar<T>(std::exp(z.real()), z.imag());
}

template<typename T>
inline Complex<T> log(const Complex<T>& z)
{
  return Complex<T>(std::log(abs(z)), arg(z)); 
}

template<typename T>
inline Complex<T> log10(const Complex<T>& z)
{
  return log(z) / std::log(static_cast<T>(10.0));
}

template<typename T>
inline Complex<T> sin(const Complex<T>& z)
{
  const T _real = z.real();
  const T _imag = z.imag();
  return Complex<T>(std::sin(_real) * std::cosh(_imag), std::cos(_real) * std::sinh(_imag));
}

template<typename T>
inline Complex<T> sinh(const Complex<T>& z)
{
  const T _real = z.real();
  const T _imag = z.imag();
  return Complex<T>(std::sinh(_real) * std::cos(_imag), std::cosh(_real) * std::sin(_imag));
}

template<typename T>
inline Complex<T> sqrt(const Complex<T>& z)
{
  if (z.real() == 0){
    T _real = std::sqrt(std::abs(z.imag()) / 2);
    T _imag = std::copysign(z.imag(), _real);
    return {_real, _imag};
  } else {
    T _abs = abs(z);
    T _real = std::sqrt((_abs + z.real())/2);
    T _imag = std::copysign(z.imag(), std::sqrt((_abs - z.real())/2));
    return {_real, _imag};
   }
}

template<typename T>
inline Complex<T> tan(const Complex<T>& z)
{
  return sin(z) / cos(z);
}

template<typename T>
inline Complex<T> tanh(const Complex<T>& z)
{
  return sinh(z) / cosh(z);
}

template<typename T>
Complex<T> pow(const Complex<T>& z, const T& n)
{
  if (z == 0) {
    return 0;
  }

  if (z.imag() == 0 && z.real() > 0) {
    return std::pow(z.real(), n);
  }

  Complex<T> temp = log(z);
  return polar<T>(std::exp(n * temp.real()), n * temp.imag());
}

template<typename T>
inline Complex<T> pow(const Complex<T>& x, const Complex<T>& y)
{
  return x == 0 ? 0 : exp(y * log(x));
}

template<typename T>
inline Complex<T> pow(const T& x, const Complex<T>& y)
{
  return x > 0
    ? polar<T>(pow(x, y.real()), y.imag() * log(x))
	  : pow(Complex<T>(x), y);
}

template<typename T>
inline Complex<T> acos(const Complex<T>& z)
{
  const Complex<T> temp = asin(z);
  return Complex<T>(M_PI / 2 - temp.real(), -temp.imag());
}

template<typename T>
inline Complex<T> asin(const Complex<T>& z)
{
  Complex<T> _asinh = asinh(Complex<T>(-z.imag(), z.real()));
  return Complex<T>(_asinh.imag(), -_asinh.real());
}

template<typename T>
inline Complex<T> atan(const Complex<T>& z)
{
  Complex<T> _atanh = atanh(Complex<T>(-z.imag(), z.real()));
  return Complex<T>(_atanh.imag(), -_atanh.real());
}

template<typename T>
inline Complex<T> acosh(const Complex<T>& z)
{
  return static_cast<T>(2.0) * log(sqrt(static_cast<T>(0.5) * (z + static_cast<T>(1.0)))
		+ sqrt(static_cast<T>(0.5) * (z - static_cast<T>(1.0))));
}

template<typename T>
inline Complex<T> asinh(const Complex<T>& z)
{
  T _real = (z.real() - z.imag()) * (z.real() + z.imag()) + static_cast<T>(1.0);
  T _imag = static_cast<T>(2.0) * z.real() * z.imag();
  Complex<T> temp(_real, _imag);

  return log(sqrt(temp) + z);
}

template<typename T>
inline Complex<T> atanh(const Complex<T>& z)
{
  const T imag_pow = std::pow(z.imag(), 2);
  const T x = static_cast<T>(1.0) - imag_pow - std::pow(z.real(), 2);

  T num = imag_pow + std::pow(static_cast<T>(1.0) + z.real(), 2);
  T den = imag_pow + std::pow(static_cast<T>(1.0) - z.real(), 2);

  T _real = static_cast<T>(0.25) * (std::log(num) - std::log(den));
  T _imag = static_cast<T>(0.5) * std::atan2(static_cast<T>(2.0) * z.imag(), x);

  return Complex<T>(_real, _imag);
}

template<class T>
Complex<T> Complex<T>::from_exponential(const Exponential<T>& z_exp)
{
    return { z_exp.r * std::cos(z_exp.phi), z_exp.r * std::sin(z_exp.phi) };

}

template<class T>
Exponential<T> Complex<T>::to_exponential() const
{
    Exponential<T> z_exp(abs(*this), 0);

    if (m_real > 0 && m_imag > 0)
    {
        z_exp.phi = std::atan(m_imag / m_real);
    }
    else if (m_real < 0 && m_imag > 0)
    {
        z_exp.phi = std::atan(m_imag / m_real) + 180;
    }
    else if (m_real < 0 && m_imag < 0)
    {
        z_exp.phi = std::atan(m_imag / m_real) + 180;
    }
    else if (m_real > 0 && m_imag < 0)
    {
        z_exp.phi = std::atan(m_imag / m_real) + 360;
    }
    else if (m_real == 0 && m_imag != 0)
    {
        throw std::invalid_argument{ "Umwandlung von kartesisch in exponential ist ohne Realteil mathematisch nicht möglich" };
    }

    return z_exp;
}