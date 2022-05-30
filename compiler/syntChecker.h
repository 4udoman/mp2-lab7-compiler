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
    while (!it.end())
    {
      std::string curStr = *it;
      std::string newStr = "";
      for (int i = 0; i < curStr.size(); i++)
      {
        if (curStr[i] != ' ')
          newStr += (char)tolower(curStr[i]);
        else if (!newStr.empty() && newStr[newStr.size() - 1] != ' ')
          newStr += ' ';
      }



      //if (lexem.find_first_of("0123456789") == 0 && lexem.find_first_not_of("0123456789.") != std::string::npos) // �������� �� ������������ ����� ����������, ���� ��� ����������
      //{
      //  std::string exc = "Invalid format of variable: " + lexem;
      //  throw exc;
      //}


    }
  }
};
