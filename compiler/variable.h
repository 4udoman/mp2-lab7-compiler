#pragma once
#include <string>

struct Variable {
  union data {
    int i;
    double d;
  };
  data val;
  bool isInt;

  Variable(bool type) : isInt(type) {}
  Variable(double dd) :isInt(0) { val.d = dd; }
  Variable(int ii) :isInt(1) { val.i = ii; }
  Variable(std::string s) {
    try { int i = stoi(s); isInt = 1; val.i = i; }
    catch (...) { isInt = 0; val.d = stod(s); }
  }

  Variable operator+(const Variable& v) {
    if (isInt && v.isInt)
      return Variable(val.i + v.val.i);
    if (isInt) // int + double = double
      return Variable(double(val.i) + v.val.d);
    return Variable(val.d + double(v.val.i));
  }
  Variable operator-() {
    if (isInt)
      return Variable(-val.i);
    return Variable(-val.d);
  }
  Variable operator-(const Variable& v) {
    if (isInt && v.isInt)
      return Variable(val.i - v.val.i);
    if (isInt) // int - float = float
      return Variable(double(val.i) - v.val.d);
    return Variable(val.d - double(v.val.i));
  }
  Variable operator*(const Variable& v) {
    if (isInt && v.isInt)
      return Variable(val.i * v.val.i);
    if (isInt) // int * float = float
      return Variable(double(val.i) * v.val.d);
    return Variable(val.d * double(v.val.i));
  }
  Variable operator/(const Variable& v) {
    if (isInt && v.isInt) // int div int = int
      return Variable(val.i / v.val.i);
    throw - 1;
  }
  Variable operator%(const Variable& v) {
    if (isInt && v.isInt) // int % int = int
      return Variable(val.i % v.val.i);
    throw - 1;
  }
};