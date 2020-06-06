#include "Complex.hpp"

template <typename T>
Complex<T> Complex<T>::from_exponential(const Exponential<T>& z_exp)
{
  return {z_exp.r * std::cos(z_exp.phi), z_exp.r * std::sin(z_exp.phi)};
}

template <typename T>
Exponential<T> Complex<T>::to_exponential() const
{
  Exponential<T> z_exp(abs(*this), 0);

  if (m_real > 0 && m_imag > 0) {
    z_exp.phi = std::atan(m_imag / m_real);
  }
  else if (m_real < 0 && m_imag > 0) {
    z_exp.phi = std::atan(m_imag / m_real) + 180;
  }
  else if (m_real < 0 && m_imag < 0) {
    z_exp.phi = std::atan(m_imag / m_real) + 180;
  }
  else if (m_real > 0 && m_imag < 0) {
    z_exp.phi = std::atan(m_imag / m_real) + 360;
  }
  else if (m_real == 0 && m_imag != 0) {
    throw std::invalid_argument{"Conversion from cartesian form to euler form "
                                "is not possible without real part"};
  }

  return z_exp;
}

template <typename T>
std::string Complex<T>::str() const
{
  if (!std::isfinite(m_imag) || !std::isfinite(m_real)) {
    throw std::invalid_argument{"Result is no finite number"};
  }
  const std::string str_imag = std::to_string(m_imag);
  if (m_real == 0) {
    return "(" + std::to_string(m_imag) + "j)";
  }
  else if (str_imag[0] != '-') {
    return "(" + std::to_string(m_real) + "+" + str_imag + "j)";
  }
  else {
    return "(" + std::to_string(m_real) + str_imag + "j)";
  }
}

template <typename T>
Complex<T>& Complex<T>::operator=(const T& rhs)
{
  m_real = rhs;
  m_imag = T();
  return *this;
}

template <typename T>
Complex<T>& Complex<T>::operator+=(const T& rhs)
{
  m_real += rhs;
  return *this;
}

template <typename T>
Complex<T>& Complex<T>::operator-=(const T& rhs)
{
  m_real -= rhs;
  return *this;
}

template <typename T>
Complex<T>& Complex<T>::operator*=(const T& rhs)
{
  m_real *= rhs;
  m_imag *= rhs;
  return *this;
}

template <typename T>
Complex<T>& Complex<T>::operator/=(const T& rhs)
{
  m_real /= rhs;
  m_imag /= rhs;
  return *this;
}

template <typename T>
template <typename U>
Complex<T>& Complex<T>::operator+=(const Complex<U>& rhs)
{
  m_real += rhs.real();
  m_imag += rhs.imag();
  return *this;
}

template <typename T>
template <typename U>
Complex<T>& Complex<T>::operator-=(const Complex<U>& rhs)
{
  m_real -= rhs.real();
  m_imag -= rhs.imag();
  return *this;
}

template <typename T>
template <typename U>
Complex<T>& Complex<T>::operator*=(const Complex<U>& rhs)
{
  const T temp = m_real * rhs.real() - m_imag * rhs.imag();
  m_imag = m_real * rhs.imag() + m_imag * rhs.real();
  m_real = temp;
  return *this;
}

template <typename T>
template <typename U>
Complex<T>& Complex<T>::operator/=(const Complex<U>& rhs)
{
  const T _norm = norm(rhs);
  const T temp = (m_real * rhs.real() + m_imag * rhs.imag()) / _norm;
  m_imag = (m_imag * rhs.real() - m_real * rhs.imag()) / _norm;
  m_real = temp;
  return *this;
}

template <typename T>
inline Complex<T> operator+(const Complex<T>& lhs, const Complex<T>& rhs)
{
  Complex<T> result = lhs;
  result += rhs;
  return result;
}

template <typename T>
inline Complex<T> operator+(const Complex<T>& lhs, const T& rhs)
{
  Complex<T> result = lhs;
  result += rhs;
  return result;
}

template <typename T>
inline Complex<T> operator+(const T& lhs, const Complex<T>& rhs)
{
  return rhs + lhs;
}

template <typename T>
inline Complex<T> operator+(const Complex<T>& rhs)
{
  return rhs;
}

template <typename T>
inline Complex<T> operator-(const Complex<T>& lhs, const Complex<T>& rhs)
{
  Complex<T> result = lhs;
  result -= rhs;
  return result;
}

template <typename T>
inline Complex<T> operator-(const Complex<T>& lhs, const T& rhs)
{
  Complex<T> result = lhs;
  result -= rhs;
  return result;
}

template <typename T>
inline Complex<T> operator-(const T& lhs, const Complex<T>& rhs)
{
  Complex<T> result = lhs;
  result -= rhs;
  return result;
}

template <typename T>
inline Complex<T> operator-(const Complex<T>& rhs)
{
  return {-rhs.real(), -rhs.imag()};
}

template <typename T>
inline Complex<T> operator*(const Complex<T>& lhs, const Complex<T>& rhs)
{
  Complex<T> result = lhs;
  result *= rhs;
  return result;
}

template <typename T>
inline Complex<T> operator*(const Complex<T>& lhs, const T& rhs)
{
  Complex<T> result = lhs;
  result *= rhs;
  return result;
}

template <typename T>
inline Complex<T> operator*(const T& lhs, const Complex<T>& rhs)
{
  return rhs * lhs;
}

template <typename T>
inline Complex<T> operator/(const Complex<T>& lhs, const Complex<T>& rhs)
{
  Complex<T> result = lhs;
  result /= rhs;
  return result;
}

template <typename T>
inline Complex<T> operator/(const Complex<T>& lhs, const T& rhs)
{
  Complex<T> result = lhs;
  result /= rhs;
  return result;
}

template <typename T>
inline Complex<T> operator/(const T& lhs, const Complex<T>& rhs)
{
  return rhs / lhs;
}

template <typename T>
inline constexpr bool operator==(const Complex<T>& lhs, const Complex<T>& rhs)
{
  return lhs.real() == rhs.real() && lhs.imag() == rhs.imag();
}

template <typename T>
inline constexpr bool operator==(const Complex<T>& lhs, const T& rhs)
{
  return lhs.real() == rhs && lhs.imag() == 0;
}

template <typename T>
inline constexpr bool operator==(const T& lhs, const Complex<T>& rhs)
{
  return rhs == lhs;
}

template <typename T>
inline constexpr bool operator!=(const Complex<T>& lhs, const Complex<T>& rhs)
{
  return !(lhs == rhs);
}

template <typename T>
inline constexpr bool operator!=(const Complex<T>& lhs, const T& rhs)
{
  return !(lhs == rhs);
}

template <typename T>
inline constexpr bool operator!=(const T& lhs, const Complex<T>& rhs)
{
  return !(lhs == rhs);
}

template <typename T, typename CharT, typename Traits>
std::basic_ostream<CharT, Traits>&
operator<<(std::basic_ostream<CharT, Traits>& os, const Complex<T>& z)
{
  return os << z.str();
}

/*************************/
/*      Utilities        */
/*************************/

template <typename T>
constexpr T real(const Complex<T>& z)
{
  return z.real();
}

template <typename T>
constexpr T imag(const Complex<T>& z)
{
  return z.imag();
}

template <typename T>
constexpr T real(const T& z)
{
  return z;
}

template <typename T>
constexpr T imag(const T&)
{
  return T();
}

template <typename T>
inline T abs(const Complex<T>& z)
{
  return std::sqrt(std::pow(z.real(), 2) + std::pow(z.imag(), 2));
}

template <typename T>
inline T arg(const Complex<T>& z)
{
  return std::atan2(z.imag(), z.real());
}

template <typename T>
inline T norm(const Complex<T>& z)
{
  return std::pow(z.real(), 2) + std::pow(z.imag(), 2);
}

template <typename T>
inline Complex<T> polar(const T& rho, const T& theta)
{
  return Complex<T>(rho * std::cos(theta), rho * std::sin(theta));
}

template <typename T>
inline Complex<T> conj(const Complex<T>& z)
{
  return Complex<T>(z.real(), -z.imag());
}

template <typename T>
inline Complex<T> cos(const Complex<T>& z)
{
  const T _real = z.real();
  const T _imag = z.imag();
  return Complex<T>(std::cos(_real) * std::cosh(_imag),
                    -std::sin(_real) * std::sinh(_imag));
}

template <typename T>
inline Complex<T> cosh(const Complex<T>& z)
{
  const T _real = z.real();
  const T _imag = z.imag();
  return Complex<T>(std::cosh(_real) * std::cos(_imag),
                    std::sinh(_real) * std::sin(_imag));
}

template <typename T>
inline Complex<T> exp(const Complex<T>& z)
{
  return polar<T>(std::exp(z.real()), z.imag());
}

template <typename T>
inline Complex<T> log(const Complex<T>& z)
{
  return Complex<T>(std::log(abs(z)), arg(z));
}

template <typename T>
inline Complex<T> log10(const Complex<T>& z)
{
  return log(z) / std::log(static_cast<T>(10.0));
}

template <typename T>
inline Complex<T> sin(const Complex<T>& z)
{
  const T _real = z.real();
  const T _imag = z.imag();
  return Complex<T>(std::sin(_real) * std::cosh(_imag),
                    std::cos(_real) * std::sinh(_imag));
}

template <typename T>
inline Complex<T> sinh(const Complex<T>& z)
{
  const T _real = z.real();
  const T _imag = z.imag();
  return Complex<T>(std::sinh(_real) * std::cos(_imag),
                    std::cosh(_real) * std::sin(_imag));
}

template <typename T>
inline Complex<T> sqrt(const Complex<T>& z)
{
  if (z.real() == 0) {
    T _real = std::sqrt(std::abs(z.imag()) / 2);
    T _imag = std::copysign(z.imag(), _real);
    return {_real, _imag};
  }
  else {
    T _abs = abs(z);
    T _real = std::sqrt((_abs + z.real()) / 2);
    T _imag = std::copysign(z.imag(), std::sqrt((_abs - z.real()) / 2));
    return {_real, _imag};
  }
}

template <typename T>
inline Complex<T> tan(const Complex<T>& z)
{
  return sin(z) / cos(z);
}

template <typename T>
inline Complex<T> tanh(const Complex<T>& z)
{
  return sinh(z) / cosh(z);
}

template <typename T>
Complex<T> pow(const Complex<T>& z, const T& n)
{
  if (z == T()) {
    return T();
  }

  if (z.imag() == 0 && z.real() > 0) {
    return std::pow(z.real(), n);
  }

  Complex<T> temp = log(z);
  return polar<T>(std::exp(n * temp.real()), n * temp.imag());
}

template <typename T>
inline Complex<T> pow(const Complex<T>& x, const Complex<T>& y)
{
  return x == T() ? T() : exp(y * log(x));
}

template <typename T>
inline Complex<T> pow(const T& x, const Complex<T>& y)
{
  return x > T() ? polar<T>(pow(x, y.real()), y.imag() * log(x))
                 : pow(Complex<T>(x), y);
}