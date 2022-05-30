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
  UnsortListTable<std::string, Variable>* table;
  std::vector<std::string> infix;
  std::vector<std::string> postfix;

  TPostfix(const TPostfix&) = delete; // Запрет на копирование
  void operator=(const TPostfix&) = delete; // Запрет на присваивание

  void ToInfix(const std::string& str);
  void ToInfixCalc(const std::string& str); // Преобразование полученной строки в vector<string> infix
  void ToPostfix(); // Преобразование infix в vector<string> postfix
  bool IsNumber(const std::string& lexem);
  double Calculate();
  bool isFunction(const std::string& str);

public:
  TPostfix() { table = nullptr; }
  TPostfix(UnsortListTable<std::string, Variable>* _table) { table = _table; }

  void Init(UnsortListTable<std::string, Variable>* _table) { table = _table; }

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
