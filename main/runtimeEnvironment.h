#pragma once
//#include "TErrors.h"
#include "executableObj.h"
#include "syntChecker.h"

class RuntimeEnvironment
{
private: // ����� �� �������� �� ����������
  // ��� ������ ���������.
public:
  RuntimeEnvironment();
  void Run();
  ~RuntimeEnvironment();
};
