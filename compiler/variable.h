#pragma once
#include <iostream>

struct Variable
{
public:
  union Data
  {
    int i;
    double d;
  };
  Data val;
  bool isInt; // true == int, false == double

  bool operator==(const Variable& var) const;
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
