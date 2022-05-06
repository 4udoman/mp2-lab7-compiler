#pragma once
#include "TErrors.h"
#include "hierarchList.h"

class SyntChecker
{
public:
  SyntChecker();
  Errors::ERRORS Check(hierList* hl);
  ~SyntChecker();
};
