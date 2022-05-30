#pragma once
#include "exitCodes.h"
#include "hierarchyList.h"

bool BracketsCorrect(const std::string& str)
{
  TStack<bool> stack; // ���� ��� �������� ������� '('
  for (const char& elem : str) {
    if (elem == '(') {
      stack.push(true);
      continue;
    }
    if (elem == ')') {
      if (stack.empty()) // ���� ���� ����, �� ��� ���� ��� ')' -> ������
        return false;
      stack.pop();
      continue;
    }
  }
  if (!stack.empty()) // ���� ���� �� ����, �� ������� ���� ')' -> ������
    return false;
  return true;
}

class SyntChecker
{
private:
  SyntChecker() = delete;
  ~SyntChecker() = delete;

public:
  static ExitCodes::CODES Check(HierarchyList* ls)
  {
    auto it = ls->begin();
    while (!1) // false
    while (!it) // true
    {

    }

  }
};
