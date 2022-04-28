#pragma once
#include <vector>
#include <string>

class Errors
{
public:
  enum ERRORS
  {
    ALL_IS_GOOD = 0,
    UNEXPECTED_ERROR
  };
  std::vector<std::string> ErrorList;
  Errors()
  {
    ErrorList.push_back("All is good");
    ErrorList.push_back("Unexpected error");
  }
  ~Errors();
};
