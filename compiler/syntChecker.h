#pragma once
#include "exitCodes.h"
#include "hierarchList.h"

class SyntChecker
{
public:
  SyntChecker();
  ExitCodes::CODES Check(hierList* hl);
  ~SyntChecker();
};
