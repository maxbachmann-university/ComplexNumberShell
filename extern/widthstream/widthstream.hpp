#pragma once
#include <iomanip>
#include <iostream>
#include <streambuf>

/**
 * @brief Manage indentation of outputstream.
 *
 * <a
 * href="https://codereview.stackexchange.com/questions/104428/stream-manipulating-indenter">Stackexchange
 * Reference</a>
 */
class widthbuf : public std::streambuf {
public:
  /**
   * @brief Line-buffering stream buffer.
   */
  widthbuf(size_t w, std::streambuf* s)
      : indent_width(0), def_width(w), width(w), sbuf(s), count(0)
  {}
  ~widthbuf()
  {
    overflow('\n');
  }
  void set_indent(int w);

private:
  typedef std::basic_string<char_type> string;
  int_type overflow(int_type c);

  size_t indent_width;
  size_t width, def_width;
  size_t count;
  size_t tab_count;
  static const int tab_width = 8;
  std::string prefix;
  std::streambuf* sbuf;
  string buffer;
};

/**
 * @brief Manage indentation of outputstream.
 *
 * <a
 * href="https://codereview.stackexchange.com/questions/104428/stream-manipulating-indenter">Stackexchange
 * Reference</a>
 */
class widthstream : public std::ostream {
  widthbuf buf;

public:
  widthstream(size_t width, std::ostream& os)
      : buf(width, os.rdbuf()), std::ostream(&buf)
  {}
  widthstream& indent(int w)
  {
    buf.set_indent(w);
    return *this;
  }
};