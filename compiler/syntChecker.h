#pragma once
#include "exitCodes.h"
#include "hierarchyList.h"

class SyntChecker
{
private:
  SyntChecker() = delete;
  ~SyntChecker() = delete;

public:
  static ExitCodes::CODES Check(HierarchyList* ls)
  {
    auto it = ls->begin();
    while ((*it) != "end.")
    {

    }

  }
};
