#pragma once
#include "TErrors.h"
#include "executableObj.h"
#include "separator.h"

class RuntimeEnvironment
{
private:
  // ��� ������ ���������.
public:
  RuntimeEnvironment();
  void Run();
  ~RuntimeEnvironment();
};
