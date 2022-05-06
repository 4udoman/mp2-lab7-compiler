#pragma once
#include <vector>
#include <string>

class Errors
{
  std::vector<std::string> ErrorList;
public:
  enum class ERRORS
  {
    ALL_IS_GOOD = 0,
    UNEXPECTED_ERROR
  };
  Errors()
  {
    ErrorList.push_back("All is good");
    ErrorList.push_back("Unexpected error");
  }
  ~Errors();
};
