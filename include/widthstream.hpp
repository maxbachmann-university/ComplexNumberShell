#pragma once
#include <iomanip>
#include <iostream>
#include <streambuf>

// taken from
// https://codereview.stackexchange.com/questions/104428/stream-manipulating-indenter

class widthbuf : public std::streambuf {
public:
  widthbuf(int w, std::streambuf* s)
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