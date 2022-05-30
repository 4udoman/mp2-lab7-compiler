#pragma once
#include <string>
#include <vector>
#include <map>
#include "stack.h"
#include "unsortListTable.h"
#include "hierarchyList.h"
using namespace std;

enum class KeyWords
{
  program = 1,
  _const,
  var,
  begin,
  end,
  _if,
  _else
};

class Functions
{
public:
  Functions()
  {

  }
  void Execute(string operation, vector<string> arguments)
  {
    
  }
};



class Operations // �����, �������� �������������� ��������
{
private:
  std::map<std::string, std::vector<int>> ops; // string - name of operation; vector<int> - priority, arity; ops - OPerationS
public:
  Operations() {// ��� ���������� �������� � �����������, ����������� ����� ����������� ������ ���� �������� � Calc � �������� ������������ � static string str_op()
    ops.emplace("*", std::vector<int>{ 2, 2 });
    ops.emplace("+", std::vector<int>{ 1, 2 });
    ops.emplace("-", std::vector<int>{ 1, 2 });
    ops.emplace("(", std::vector<int>{ 0, 0 });
    ops.emplace(")", std::vector<int>{ 0, 0 });
    ops.emplace("mod", std::vector<int>{ 3, 1 });
    ops.emplace("div", std::vector<int>{ 3, 1 });
  }

  static std::string str_op() { return std::string("*, +, -, (, ), mod, div"); }

  bool IsOperation(const std::string& elem) const { return ops.find(elem) != ops.end(); } // �������� �������� �� ������ ������� ���������, ������� ��������� � ������

  int GetPriority(const std::string& elem) { return ops[elem][0]; } // �������� ��������� � �������� ��������, �������� ������������� �� ������������� 

  int GetArity(const std::string& elem) { return ops[elem][1]; } // �������� ������� � �������� ��������, �������� ������������� �� ������������� 

  int Calc(const std::string& elem, int left, int right = int()) {// ���������
    if (elem == "*")
      return left * right;
    if (elem == "+")
      return  left + right;
    if (elem == "-")
      return left - right;
    if (elem == "mod")
      return left % right;
    if (elem == "div")
      return left / right;
  }
};

class TPostfix {
private:
  Operations operation;
  UnsortListTable<std::string, int>* tableInt;
  UnsortListTable<std::string, double>* tableDouble;
  std::vector<std::string> infix;
  std::vector<std::string> postfix;
  TPostfix(const TPostfix&) = delete; // ������ �� �����������
  void operator=(const TPostfix&) = delete; // ������ �� ������������
  bool BracketsCorrect(const std::string& str) const; // �������� �� ������������ ����������� ������ � ���������� �� ���� ������
  void ToInfix(const std::string& str);
  void ToInfixCalc(const std::string& str);// �������������� ���������� ������ � vector<string> infix
  void ToPostfix(); // �������������� infix � vector<string> postfix
  bool IsNumber(const std::string& lexem);
  void DeleteSpaces(std::string& str);
  double Calculate();
  KeyWords KeyWord(const string& str);
  bool IsFunction(const string& str);

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

  void NewInfix(const string& str)
  {
    if (BracketsCorrect(str) == false) 
      throw string("BracketsError");    
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
