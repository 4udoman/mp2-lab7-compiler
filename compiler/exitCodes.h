#pragma once

struct ExitCodes
{
  static const char* ErrorList[]; 
  enum class CODES
  {
    ALL_IS_GOOD = 0,
    UNEXPECTED_ERROR
  };
};

const char* ExitCodes::ErrorList[] = {
    "All is good",
    "Unexpected error"
};