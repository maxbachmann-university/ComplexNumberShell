#include "widthstream.hpp"

void widthbuf::set_indent(int w)
{
  if (w == 0) {
    prefix.clear();
    indent_width = 0;
    width = def_width;
  }
  else {
    indent_width += w;
    prefix = std::string(indent_width, ' ');
    width -= w;
  }
}

// This is basically a line-buffering stream buffer.
// The algorithm is:
// - Explicit end of line ("\r" or "\n"): we flush our buffer
//   to the underlying stream's buffer, and set our record of
//   the line length to 0.
// - An "alert" character: sent to the underlying stream
//   without recording its length, since it doesn't normally
//   affect the a appearance of the output.
// - tab: treated as moving to the next tab stop, which is
//   assumed as happening every tab_width characters.
// - Everything else: really basic buffering with word wrapping.
//   We try to add the character to the buffer, and if it exceeds
//   our line width, we search for the last space/tab in the
//   buffer and break the line there. If there is no space/tab,
//   we break the line at the limit.
widthbuf::int_type widthbuf::overflow(int_type c)
{
  if (traits_type::eq_int_type(traits_type::eof(), c))
    return traits_type::not_eof(c);

  switch (c) {
  case '\n':
  case '\r':
  {
    buffer += c;
    count = 0;
    sbuf->sputn(prefix.c_str(), indent_width);
    int_type rc = sbuf->sputn(buffer.c_str(), buffer.size());
    buffer.clear();
    return rc;
  }
  case '\a':
    return sbuf->sputc(c);
  case '\t':
    buffer += c;
    count += tab_width - count % tab_width;
    return c;
  default:
    if (count >= width) {
      size_t wpos = buffer.find_last_of(" \t");
      if (wpos != string::npos) {
        sbuf->sputn(prefix.c_str(), indent_width);
        sbuf->sputn(buffer.c_str(), wpos);
        count = buffer.size() - wpos - 1;
        buffer = string(buffer, wpos + 1);
      }
      else {
        sbuf->sputn(prefix.c_str(), indent_width);
        sbuf->sputn(buffer.c_str(), buffer.size());
        buffer.clear();
        count = 0;
      }
      sbuf->sputc('\n');
    }
    buffer += c;
    ++count;
    return c;
  }
}