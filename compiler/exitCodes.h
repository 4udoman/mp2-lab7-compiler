#pragma once
#include <iostream>

struct ExitCodes
{
  static const char* ErrorList[]; 
  enum CODES
  {
    ALL_IS_GOOD = 0,
    INCORRECT_PROGRAM_NAME,
    UNEXPECTED_EXPRESSION,
    INCORRECT_VARIABLE_NAME,
    SEPARATOR_WAS_EXPECTED,
    INVALID_VARIABLE_TYPE,
    INVALID_VARIABLE_VALUE,
    DOUBLE_DECLARATION,

    SEMICOLON_IS_REQUIRED,
    INCORRECT_ORDER_WITH_PROGRAM,
    INCORRECT_ORDER_WITH_CONST,
    INCORRECT_ORDER_WITH_VAR,
    UNABLE_TO_CREATE_SECOND_PROGRAM,
    UNABLE_TO_CREATE_CONST,
    UNABLE_TO_CREATE_VAR,


    NO_SUCH_VARIABLE,
    DIVISION_BY_ZERO,
    UNEXPECTED_ERROR,
    NOT_ENOUGH_ARGUMENTS_TO_CALL_THE_FUNCTION
  };
  friend std::ostream& operator<<(std::ostream& os, const ExitCodes::CODES& err) {
    os << ExitCodes::ErrorList[err] << std::endl;
    return os;
  }
};

const char* ExitCodes::ErrorList[] = {
    "All is good",
    "Incorrect program name",
    "Unexpected expression",
    "Incorrect variable name",
    "Separator was expected",
    "Invalid variable type",
    "Invalid variable value",
    "Double declaration",

    "Semicolon is required",
    "Incorrect order with program",
    "Incorrect order with const",
    "Incorrect order with var",
    "Unable to create second program",
    "Unable to create const",
    "Unable to create var",



    "No such variable",
    "Division by zero",
    "Unexpected error"
    "Not_enough_argumets_to_call_the_function"
};
