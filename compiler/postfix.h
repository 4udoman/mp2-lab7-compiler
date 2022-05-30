#pragma once
#include <string>
#include <vector>
#include "syntax.h"
#include "stack.h"
#include "unsortListTable.h"
#include "hierarchyList.h"

class TPostfix {
private:
  Operations operation;
  UnsortListTable<std::string, int>* tableInt;
  UnsortListTable<std::string, double>* tableDouble;
  std::vector<std::string> infix;
  std::vector<std::string> postfix;

  TPostfix(const TPostfix&) = delete; // Запрет на копирование
  void operator=(const TPostfix&) = delete; // Запрет на присваивание
  bool BracketsCorrect(const std::string& str) const; // Проверка на корректность раставления скобок в полученной на вход строке
  void ToInfix(const std::string& str);
  void ToInfixCalc(const std::string& str);// Преобразование полученной строки в vector<string> infix
  void ToPostfix(); // Преобразование infix в vector<string> postfix
  bool IsNumber(const std::string& lexem);
  void DeleteSpaces(std::string& str);
  double Calculate();
  bool isFunction(const std::string& str);

public:
  TPostfix()
  {

  }
  TPostfix(UnsortListTable<std::string, int>* _tableInt, UnsortListTable<std::string, double>* _tableDouble)
  {
    tableInt = _tableInt;
    tableDouble = _tableDouble;
  }

  void Init(UnsortListTable<std::string, int>* _tableInt, UnsortListTable<std::string, double>* _tableDouble)
  {
    tableInt = _tableInt;
    tableDouble = _tableDouble;
  }

  void NewInfix(const std::string& str)
  {
    ToInfix(str);
    ToPostfix();
  }

  std::vector<std::string> GetInfix() const { return infix; }
  std::vector<std::string> GetPostfix() const { return postfix; }

  std::string GetStringInfix() const {
    std::string tmp;
    for (const std::string& elem : infix)
      tmp += elem + ' ';
    return tmp;
  }

  std::string GetStringPostfix() const {
    std::string tmp;
    for (const std::string& elem : postfix)
      tmp += elem + ' ';
    return tmp;
  }

  void Execute(HierarchyList::iterator* it);
  
};
