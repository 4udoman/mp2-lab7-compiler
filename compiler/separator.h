#pragma once
#include "TErrors.h"
#include "hierarchList.h"

class Separator
{
public:
  Separator();
  Errors::ERRORS Checker(hierList hl);
  ~Separator();
};
