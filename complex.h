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
  constexpr complex(const T& r = T(), const T& i = T())
    : m_real(r), m_imag(i) { }

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

  complex<T>& operator+=(const T& val) {
	  m_real += val;
	  return *this;
  }

  complex<T>& operator-=(const T& val) {
	  m_real -= val;
	  return *this;
  }

  complex<T>& operator*=(const T&);

  template<typename U>
  complex<T>& operator*=(const complex<U>&);

  complex<T>& operator/=(const T&);

  template<typename U>
  complex<T>& operator/=(const complex<U>&);

  template<typename U>
  complex<T>& operator+=(const complex<U>&);
  
  template<typename U>
  complex<T>& operator-=(const complex<U>&);

private:
  T m_real;
  T m_imag;
};

template<typename T>
complex<T>& complex<T>::operator=(const T& val) {
  m_real = val;
  m_imag = 0;
  return *this;
}

template<typename T>
complex<T>&
complex<T>::operator*=(const T& val)
{
  m_real *= val;
  m_imag *= val;
  return *this;
}

template<typename T>
complex<T>& complex<T>::operator/=(const T& val)
{
  m_real /= val;
  m_imag /= val;
  return *this;
}

template<typename T>
template<typename U>
complex<T>& complex<T>::operator+=(const complex<U>& z)
{
  m_real += z.real();
  m_imag += z.imag();
  return *this;
}

template<typename T>
template<typename U>
complex<T>& complex<T>::operator-=(const complex<U>& z)
{
  m_real -= z.real();
  m_imag -= z.imag();
  return *this;
}

template<typename T>
template<typename U>
complex<T>& complex<T>::operator*=(const complex<U>& z)
{
  const T r = m_real * z.real() - m_imag * z.imag();
  m_imag = m_real * z.imag() + m_imag * z.real();
  m_real = r;
  return *this;
}

template<typename T>
template<typename U>
complex<T>& complex<T>::operator/=(const complex<U>& z)
{
  const T r =  m_real * z.real() + m_imag * z.imag();
  const T n = norm(z);
  m_imag = (m_imag * z.real() - m_real * z.imag()) / n;
  m_real = r / n;
  return *this;
}

template<typename T>
inline complex<T> operator+(const complex<T>& x, const complex<T>& y)
{
  complex<T> r = x;
  r += y;
  return r;
}

template<typename T>
inline complex<T> operator+(const complex<T>& x, const T& y)
{
  complex<T> r = x;
  r += y;
  return r;
}

template<typename T>
inline complex<T> operator+(const T& x, const complex<T>& y)
{
  return y + x;
}

template<typename T>
inline complex<T> operator+(const complex<T>& x)
{
	return x;
}


template<typename T>
inline complex<T>
operator-(const complex<T>& x, const complex<T>& y)
{
  complex<T> r = x;
  r -= y;
  return r;
}

template<typename T>
inline complex<T>
operator-(const complex<T>& x, const T& y)
{
  complex<T> r = x;
  r -= y;
  return r;
}

template<typename T>
inline complex<T>
operator-(const T& x, const complex<T>& y)
{
  complex<T> r = -y;
  r += x;
  return r;
}

template<typename T>
inline complex<T>
operator-(const complex<T>& x)
{
	return complex<T>(-x.real(), -x.imag());
}

template<typename T>
inline complex<T> operator*(const complex<T>& x, const complex<T>& y)
{
  complex<T> r = x;
  r *= y;
  return r;
}

template<typename T>
inline complex<T>
operator*(const complex<T>& x, const T& y)
{
  complex<T> r = x;
  r *= y;
  return r;
}

template<typename T>
inline complex<T>
operator*(const T& x, const complex<T>& y)
{
  return y * x;
}

template<typename T>
inline complex<T>
operator/(const complex<T>& x, const complex<T>& y)
{
  complex<T> r = x;
  r /= y;
  return r;
}

template<typename T>
inline complex<T> operator/(const complex<T>& x, const T& y)
{
  complex<T> r = x;
  r /= y;
  return r;
}

template<typename T>
inline complex<T> operator/(const T& x, const complex<T>& y)
{
  return y / x;
}

template<typename T>
inline constexpr bool operator==(const complex<T>& x, const complex<T>& y)
{
  return x.real() == y.real() && x.imag() == y.imag();
}

template<typename T>
inline constexpr bool operator==(const complex<T>& x, const T& y)
{
  return x.real() == y && x.imag() == 0;
}

template<typename T>
inline constexpr bool operator==(const T& x, const complex<T>& y)
{
  return y == x;
}

template<typename T>
inline constexpr bool operator!=(const complex<T>& x, const complex<T>& y)
{
  return !(x == y);
}

template<typename T>
inline constexpr bool operator!=(const complex<T>& x, const T& y)
{
  return !(x == y);
}

template<typename T>
inline constexpr bool
operator!=(const T& x, const complex<T>& y)
{
  return !(x == y);
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
  T r = z.real();
  T i = z.imag();
  const T s = std::max(std::abs(r), std::abs(i));
  if (s == 0) {
    return s;
  }
  r /= s;
  i /= s;
  return s * std::sqrt(std::pow(r, 2) + std::pow(i, 2));
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
  const T r = z.real();
  const T i = z.imag();
  return complex<T>(std::cos(r) * std::cosh(i), -std::sin(r) * std::sinh(i));
}

template<typename T>
inline complex<T> cosh(const complex<T>& z)
{
  const T r = z.real();
  const T i = z.imag();
  return complex<T>(std::cosh(r) * std::cos(i), std::sinh(r) * std::sin(i));
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
  const T r = z.real();
  const T i = z.imag();
  return complex<T>(std::sin(r) * std::cosh(i), std::cos(r) * std::sinh(i));
}

template<typename T>
inline complex<T> sinh(const complex<T>& z)
{
  const T r = z.real();
  const T  i = z.imag();
  return complex<T>(std::sinh(r) * std::cos(i), std::cosh(r) * std::sin(i));
}

template<typename T>
inline complex<T> sqrt(const complex<T>& z)
{
  T r = z.real();
  T i = z.imag();

  if (r == 0){
    T root = std::sqrt(std::abs(i) / 2);
    return complex<T>(root, i < 0 ? -root : root);
  } else {
    T root = std::sqrt(2 * (std::abs(z) + std::abs(r)));
    T root_2 = root / 2;
    return r > 0
      ? complex<T>(root_2, i / root)
      : complex<T>(std::abs(i) / root, i < 0 ? -root_2 : root_2);
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
complex<T> pow(const complex<T>& x, const T& n)
{
  if (x == 0) {
    return 0;
  }

  if (x.imag() == 0 && x.real() > 0) {
    return std::pow(x.real(), n);
  }

  complex<T> temp = log(x);
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
  const T r2 = std::pow(z.real(), 2);
  const T x = T(1.0) - r2 - std::pow(z.imag(), 2);

  T num = z.imag() + T(1.0);
  T den = z.imag() - T(1.0);

  T _imag = T(0.25) * (r2 + std::pow(num, 2)) / (r2 + std::pow(den, 2));

  return complex<T>(T(0.5) * std::atan2(T(2.0) * z.real(), x), _imag);
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
  const T i2 = std::pow(z.imag(), 2);
  const T x = T(1.0) - i2 - std::pow(z.real(), 2);

  T num = T(1.0) + z.real();
  T den = T(1.0) - z.real();

  num = i2 + std::pow(num, 2);
  den = i2 + std::pow(den, 2);

  T _real = T(0.25) * (std::log(num) - std::log(den));

  return complex<T>(_real, T(0.5) * std::atan2(T(2.0) * z.imag(), x));
}