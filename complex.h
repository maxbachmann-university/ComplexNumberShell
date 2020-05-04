#include <cmath>
#include <algorithm>
#include <ostream>

// Forward declarations.
template<typename T> struct complex;

///  Return magnitude.
template<typename T> T abs(const complex<T>&);
///  Return phase angle.
template<typename T> T arg(const complex<T>&);
///  Return squared magnitude.
template<typename T> T norm(const complex<T>&);
///  Return complex conjugate.
template<typename T> complex<T> conj(const complex<T>&);
///  Return complex with magnitude rho and angle theta.
template<typename T> complex<T> polar(const T&, const T& = T());

/// Return complex cosine.
template<typename T> complex<T> cos(const complex<T>&);
/// Return complex hyperbolic cosine.
template<typename T> complex<T> cosh(const complex<T>&);
/// Return complex base e exponential.
template<typename T> complex<T> exp(const complex<T>&);
/// Return complex natural logarithm.
template<typename T> complex<T> log(const complex<T>&);
/// Return complex base 10 logarithm.
template<typename T> complex<T> log10(const complex<T>&);
/// Return Tx to the y'th power.
template<typename T> complex<T> pow(const complex<T>&, const T&);
/// Return Tx to the y'th power.
template<typename T> complex<T> pow(const complex<T>&, const complex<T>&);
/// Return Tx to the y'th power.
template<typename T> complex<T> pow(const T&, const complex<T>&);
/// Return complex sine.
template<typename T> complex<T> sin(const complex<T>&);
/// Return complex hyperbolic sine.
template<typename T> complex<T> sinh(const complex<T>&);
/// Return complex square root.
template<typename T> complex<T> sqrt(const complex<T>&);
/// Return complex tangent.
template<typename T> complex<T> tan(const complex<T>&);
/// Return complex hyperbolic tangent.
template<typename T> complex<T> tanh(const complex<T>&);
/// Return complex inverse cosine.
template<typename T> complex<T> acos(const complex<T>&);
/// Return complex inverse sine.
template<typename T> complex<T> asin(const complex<T>&);
/// Return complex inverse tangent.
template<typename T> complex<T> atan(const complex<T>&);
/// Return complex inverse hyperbolic cosine.
template<typename T> complex<T> acosh(const complex<T>&);
/// Return complex inverse hyperbolic sine.
template<typename T> complex<T> asinh(const complex<T>&);
/// Return complex inverse hyperbolic tangent.
template<typename T> complex<T> atanh(const complex<T>&);


template<typename T>
struct complex
{
  constexpr complex(const T& real = T(), const T& imag = T())
    : m_real(real), m_imag(imag) { }

  constexpr complex(const complex&) = default;

  template<typename U>
  constexpr complex(const complex<U>& z)
	  : m_real(z.real()), m_imag(z.imag()) { }

  complex<T>& operator=(const T&);

  complex& operator=(const complex&) = default;

  constexpr T real() const { return m_real; }
  constexpr T imag() const { return m_imag; }

  void real(T val) { m_real = val; }
  void imag(T val) { m_imag = val; }

  complex<T>& operator+=(const T&);

  template<typename U>
  complex<T>& operator+=(const complex<U>&);

  complex<T>& operator-=(const T&);

  template<typename U>
  complex<T>& operator-=(const complex<U>&);

  complex<T>& operator*=(const T&);

  template<typename U>
  complex<T>& operator*=(const complex<U>&);

  complex<T>& operator/=(const T&);

  template<typename U>
  complex<T>& operator/=(const complex<U>&);

private:
  T m_real;
  T m_imag;
};

template<typename T>
complex<T>& complex<T>::operator=(const T& rhs) {
  m_real = rhs;
  m_imag = T();
  return *this;
}

template<typename T>
complex<T>& complex<T>::operator+=(const T& rhs) {
  m_real += rhs;
	return *this;
}

template<typename T>
complex<T>& complex<T>::operator-=(const T& rhs) {
  m_real -= rhs;
  return *this;
}

template<typename T>
complex<T>& complex<T>::operator*=(const T& rhs)
{
  m_real *= rhs;
  m_imag *= rhs;
  return *this;
}

template<typename T>
complex<T>& complex<T>::operator/=(const T& rhs)
{
  m_real /= rhs;
  m_imag /= rhs;
  return *this;
}

template<typename T>
template<typename U>
complex<T>& complex<T>::operator+=(const complex<U>& rhs)
{
  m_real += rhs.real();
  m_imag += rhs.imag();
  return *this;
}

template<typename T>
template<typename U>
complex<T>& complex<T>::operator-=(const complex<U>& rhs)
{
  m_real -= rhs.real();
  m_imag -= rhs.imag();
  return *this;
}

template<typename T>
template<typename U>
complex<T>& complex<T>::operator*=(const complex<U>& rhs)
{
  const T temp = m_real * rhs.real() - m_imag * rhs.imag();
  m_imag = m_real * rhs.imag() + m_imag * rhs.real();
  m_real = temp;
  return *this;
}

template<typename T>
template<typename U>
complex<T>& complex<T>::operator/=(const complex<U>& rhs)
{
  const T _norm = norm(rhs);
  const T temp = (m_real * rhs.real() + m_imag * rhs.imag()) / _norm;
  m_imag = (m_imag * rhs.real() - m_real * rhs.imag()) / _norm;
  m_real = temp;
  return *this;
}

template<typename T>
inline complex<T> operator+(const complex<T>& lhs, const complex<T>& rhs)
{
  complex<T> result = lhs;
  result += rhs;
  return result;
}

template<typename T>
inline complex<T> operator+(const complex<T>& lhs, const T& rhs)
{
  complex<T> result = lhs;
  result += rhs;
  return result;
}

template<typename T>
inline complex<T> operator+(const T& lhs, const complex<T>& rhs)
{
  return rhs + lhs;
}

template<typename T>
inline complex<T> operator+(const complex<T>& rhs)
{
	return rhs;
}


template<typename T>
inline complex<T> operator-(const complex<T>& lhs, const complex<T>& rhs)
{
  complex<T> result = lhs;
  result -= rhs;
  return result;
}

template<typename T>
inline complex<T> operator-(const complex<T>& lhs, const T& rhs)
{
  complex<T> result = lhs;
  result -= rhs;
  return result;
}

template<typename T>
inline complex<T> operator-(const T& lhs, const complex<T>& rhs)
{
  complex<T> result = -rhs;
  result += lhs;
  return result;
}

template<typename T>
inline complex<T> operator-(const complex<T>& rhs)
{
	return complex<T>(-rhs.real(), -rhs.imag());
}

template<typename T>
inline complex<T> operator*(const complex<T>& lhs, const complex<T>& rhs)
{
  complex<T> result = lhs;
  result *= rhs;
  return result;
}

template<typename T>
inline complex<T> operator*(const complex<T>& lhs, const T& rhs)
{
  complex<T> result = lhs;
  result *= rhs;
  return result;
}

template<typename T>
inline complex<T> operator*(const T& lhs, const complex<T>& rhs)
{
  return rhs * lhs;
}

template<typename T>
inline complex<T> operator/(const complex<T>& lhs, const complex<T>& rhs)
{
  complex<T> result = lhs;
  result /= rhs;
  return result;
}

template<typename T>
inline complex<T> operator/(const complex<T>& lhs, const T& rhs)
{
  complex<T> result = lhs;
  result /= rhs;
  return result;
}

template<typename T>
inline complex<T> operator/(const T& lhs, const complex<T>& rhs)
{
  return rhs / lhs;
}

template<typename T>
inline constexpr bool operator==(const complex<T>& lhs, const complex<T>& rhs)
{
  return lhs.real() == rhs.real() && lhs.imag() == rhs.imag();
}

template<typename T>
inline constexpr bool operator==(const complex<T>& lhs, const T& rhs)
{
  return lhs.real() == rhs && lhs.imag() == 0;
}

template<typename T>
inline constexpr bool operator==(const T& lhs, const complex<T>& rhs)
{
  return rhs == lhs;
}

template<typename T>
inline constexpr bool operator!=(const complex<T>& lhs, const complex<T>& rhs)
{
  return !(lhs == rhs);
}

template<typename T>
inline constexpr bool operator!=(const complex<T>& lhs, const T& rhs)
{
  return !(lhs == rhs);
}

template<typename T>
inline constexpr bool operator!=(const T& lhs, const complex<T>& rhs)
{
  return !(lhs == rhs);
}

template<typename T, typename CharT, class Traits>
std::basic_ostream<CharT, Traits>&
operator<<(std::basic_ostream<CharT, Traits>& os, const complex<T>& z)
{
  if (z.real() == 0) {
    return os << z.imag() << "j";
  } else if (z.imag() >= 0) {
    return os << "(" << z.real() << "+" << z.imag() << "j)";
  } else {
    return os << "(" << z.real() << z.imag() << "j)";
  }
}


/*************************/
/*      Utilities        */
/*************************/

template<typename T>
constexpr T real(const complex<T>& z)
{
  return z.real();
}

template<typename T>
constexpr T imag(const complex<T>& z)
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
inline T abs(const complex<T>& z)
{
  T _real = z.real();
  T _imag = z.imag();
  const T s = std::max(std::abs(_real), std::abs(_imag));
  if (s == 0) {
    return s;
  }
  _real /= s;
  _imag /= s;
  return s * std::sqrt(std::pow(_real, 2) + std::pow(_imag, 2));
}

template<typename T>
inline T arg(const complex<T>& z)
{
  return std::atan2(z.imag(), z.real());
}

template<typename T>
inline T norm(const complex<T>& z)
{
  return std::pow(z.real(), 2) + std::pow(z.imag(), 2);
}

template<typename T>
inline complex<T> polar(const T& rho, const T& theta)
{
  return complex<T>(rho * std::cos(theta), rho * std::sin(theta));
}

template<typename T>
inline complex<T> conj(const complex<T>& z)
{
  return complex<T>(z.real(), -z.imag());
}

template<typename T>
inline complex<T> cos(const complex<T>& z)
{
  const T _real = z.real();
  const T _imag = z.imag();
  return complex<T>(std::cos(_real) * std::cosh(_imag), -std::sin(_real) * std::sinh(_imag));
}

template<typename T>
inline complex<T> cosh(const complex<T>& z)
{
  const T _real = z.real();
  const T _imag = z.imag();
  return complex<T>(std::cosh(_real) * std::cos(_imag), std::sinh(_real) * std::sin(_imag));
}

template<typename T>
inline complex<T> exp(const complex<T>& z)
{
  return polar<T>(std::exp(z.real()), z.imag());
}

template<typename T>
inline complex<T> log(const complex<T>& z)
{
  return complex<T>(std::log(abs(z)), arg(z)); 
}

template<typename T>
inline complex<T> log10(const complex<T>& z)
{
  return log(z) / std::log(T(10.0));
}

template<typename T>
inline complex<T> sin(const complex<T>& z)
{
  const T _real = z.real();
  const T _imag = z.imag();
  return complex<T>(std::sin(_real) * std::cosh(_imag), std::cos(_real) * std::sinh(_imag));
}

template<typename T>
inline complex<T> sinh(const complex<T>& z)
{
  const T _real = z.real();
  const T _imag = z.imag();
  return complex<T>(std::sinh(_real) * std::cos(_imag), std::cosh(_real) * std::sin(_imag));
}

template<typename T>
inline complex<T> sqrt(const complex<T>& z)
{
  T _real = z.real();
  T _imag = z.imag();

  if (_real == 0){
    T _sqrt = std::sqrt(std::abs(_imag) / 2);
    return complex<T>(_sqrt, _imag < 0 ? -_sqrt : _sqrt);
  } else {
    T _sqrt = std::sqrt(2 * (abs(z) + std::abs(_real)));
    T _sqrt_2 = _sqrt / 2;
    return _real > 0
      ? complex<T>(_sqrt_2, _imag / _sqrt)
      : complex<T>(std::abs(_imag) / _sqrt, _imag < 0 ? -_sqrt_2 : _sqrt_2);
   }
}

template<typename T>
inline complex<T> tan(const complex<T>& z)
{
  return sin(z) / cos(z);
}

template<typename T>
inline complex<T> tanh(const complex<T>& z)
{
  return sinh(z) / cosh(z);
}

template<typename T>
complex<T> pow(const complex<T>& z, const T& n)
{
  if (z == 0) {
    return 0;
  }

  if (z.imag() == 0 && z.real() > 0) {
    return std::pow(z.real(), n);
  }

  complex<T> temp = log(z);
  return polar<T>(std::exp(n * temp.real()), n * temp.imag());
}

template<typename T>
inline complex<T> pow(const complex<T>& x, const complex<T>& y)
{
  return x == 0 ? 0 : exp(y * log(x));
}

template<typename T>
inline complex<T> pow(const T& x, const complex<T>& y)
{
  return x > 0
    ? polar<T>(pow(x, y.real()), y.imag() * log(x))
	  : pow(complex<T>(x), y);
}

template<typename T>
inline complex<T> acos(const complex<T>& z)
{
  const complex<T> temp = asin(z);
  return complex<T>(M_PI / 2 - temp.real(), -temp.imag());
}

template<typename T>
inline complex<T> asin(const complex<T>& z)
{
  complex<T> temp(-z.imag(), z.real());
  temp = asinh(temp);
  return complex<T>(temp.imag(), -temp.real());
}

template<typename T>
inline complex<T> atan(const complex<T>& z)
{
  complex<T> _atanh = atanh(complex<T>(-z.imag(), z.real()));
  return complex<T>(_atanh.imag(), -_atanh.real());
}

template<typename T>
inline complex<T> acosh(const complex<T>& z)
{
  return T(2.0) * log(sqrt(T(0.5) * (z + T(1.0)))
		+ sqrt(T(0.5) * (z - T(1.0))));
}

template<typename T>
inline complex<T> asinh(const complex<T>& z)
{
  T _real = (z.real() - z.imag()) * (z.real() + z.imag()) + T(1.0);
  T _imag = T(2.0) * z.real() * z.imag();
  complex<T> temp(_real, _imag);

  return log(sqrt(temp) + z);
}

template<typename T>
inline complex<T> atanh(const complex<T>& z)
{
  const T imag_pow = std::pow(z.imag(), 2);
  const T x = T(1.0) - imag_pow - std::pow(z.real(), 2);

  T num = T(1.0) + z.real();
  T den = T(1.0) - z.real();

  num = imag_pow + std::pow(num, 2);
  den = imag_pow + std::pow(den, 2);

  T _real = T(0.25) * (std::log(num) - std::log(den));
  T _imag = T(0.5) * std::atan2(T(2.0) * z.imag(), x);

  return complex<T>(_real, _imag);
}