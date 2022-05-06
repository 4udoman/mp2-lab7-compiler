#pragma once
#include <vector>
#include <string>

class ExitCodes
{
  std::vector<std::string> ErrorList;
public:
  enum class CODES
  {
    ALL_IS_GOOD = 0,
    UNEXPECTED_ERROR
  };
  ExitCodes()
  {
    ErrorList.push_back("All is good");
    ErrorList.push_back("Unexpected error");
  }
  ~ExitCodes();
};
