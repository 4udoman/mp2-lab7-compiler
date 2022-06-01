#pragma once
#include <iostream>

struct ExitCodes
{
  static const char* ErrorList[]; 
  enum CODES
  {
    ALL_IS_GOOD = 0,
    DIVISION_BY_ZERO,
    UNEXPECTED_ERROR
  };
  friend std::ostream& operator<<(std::ostream& os, const ExitCodes::CODES& err) {
    os << ExitCodes::ErrorList[err] << std::endl;
    return os;
  }
};

const char* ExitCodes::ErrorList[] = {
    "All is good",
    "Division by zero",
    "Unexpected error"
};
