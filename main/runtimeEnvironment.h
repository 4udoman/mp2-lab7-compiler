#pragma once
//#include "TErrors.h"
#include "executableObj.h"
#include "syntChecker.h"

class RuntimeEnvironment
{
private: // Набор из программ не обязателен
  // Это просто интерфейс.
public:
  RuntimeEnvironment();
  void Run();
  ~RuntimeEnvironment();
};
