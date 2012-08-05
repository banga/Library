/*
 * Indentable.h
 *
 * Wrapper for ostream objects to indent/dedent lines automatically, especially
 * useful for debugging recursive functions.
 *
 * usage:
 *
 * Indentable i(cout, 4, 2);
 * function Recursive(...) {
 *  ScopedIndent scoped(i);
 *  i << "..." << endl;
 *  ...
 *  Recursive(...)
 * }
 *
 */

#ifndef __SHREY_LIB_INDENTABLE_H__
#define __SHREY_LIB_INDENTABLE_H__

#include <algorithm>
#include <iostream>
#include <string>

namespace lib {

using std::cout;
using std::endl;
using std::max;
using std::ostream;
using std::string;

class Indentable {
public:
  explicit Indentable(ostream& out, int indent_size = 0, int indent_increment = 2)
    : out_(out),
      indent_size_(indent_size),
      indent_increment_(indent_increment),
      indent_pending_(true),
      endl_addr_(&endl) { }

  void Indent() {
    indent_size_ += indent_increment_;
  }
  void Dedent() {
    indent_size_ = max(indent_size_ - indent_increment_, 0);
  }

  template <typename T>
  Indentable& operator << (const T& t) {
    indent_if_pending();
    out_ << t;
    return *this;
  }

  Indentable& operator << (char c) {
    indent_if_pending();
    if (c == '\n') set_indent_pending();
    out_ << c;
    return *this;
  }

  Indentable& operator << (const char* str) {
    while(*str) {
      indent_if_pending();
      out_ << *str;
      if(*str++ == '\n') set_indent_pending();
    }
    return *this;
  }

  Indentable& operator << (const string& str) {
    for(size_t i = 0; i < str.length(); ++i) {
      indent_if_pending();
      out_ << str[i];
      if (str[i] == '\n') set_indent_pending();
    }
    return *this;
  }

  Indentable& operator << (ostream& (*pf) (ostream&)) {
    indent_if_pending();
    if (pf == endl_addr_) set_indent_pending();
    out_ << pf;
    return *this;
  }

private:
  ostream& out_;
  int indent_size_, indent_increment_;
  bool indent_pending_;
  ostream& (*endl_addr_) (ostream&);

  void set_indent_pending() { indent_pending_ = true; }
  void indent() {
    out_ << string(indent_size_, ' ');
  }
  void indent_if_pending() {
    if (indent_pending_) {
      indent();
      indent_pending_ = false;
    }
  }
};

/*
 * Helper class to match indent/dedent with a block or function scope
 */
class ScopedIndent {
public:
  ScopedIndent(Indentable& indentable)
    : indentable_(indentable) {
    indentable_.Indent();
  }
  ~ScopedIndent() {
    indentable_.Dedent();
  }
private:
  Indentable& indentable_;
};

Indentable icout(cout);

}  // namespace lib

#endif
