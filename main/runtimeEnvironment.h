#pragma once
#include "TErrors.h"
#include "executableObj.h"
#include "separator.h"

class RuntimeEnvironment
{
private:
  // Это просто интерфейс.
public:
  RuntimeEnvironment();
  void Run();
  ~RuntimeEnvironment();
};
