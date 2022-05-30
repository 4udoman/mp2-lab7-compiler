#pragma once
#include <iostream>

struct Variable
{
public:
  union Var
  {
    double d;
    int i;
  };
  Var v;
  bool type; // false == int, true == double

  bool operator==(const Variable& var) const;
  bool operator!=(const Variable& var) const;
  bool operator<(const Variable& var) const;
  bool operator>(const Variable& var) const;
  bool operator<=(const Variable& var) const;
  bool operator>=(const Variable& var) const;
  
  Variable& operator=(const Variable& var);

  Variable  operator+(const Variable& var);
  Variable  operator-(const Variable& var);
  Variable  operator*(const Variable& var);
  Variable  operator%(const Variable& var);
  Variable  operator/(const Variable& var);

  friend std::istream& operator>>(std::istream& in, Variable& var);

  friend std::ostream& operator<<(std::ostream& out, const Variable& var);
};
