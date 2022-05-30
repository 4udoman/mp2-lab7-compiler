#pragma once
#include <map>
#include <vector>
#include <iostream>
#include "variable.h"

enum class KeyWords
{
  _program = 1,
  _const,
  _var,
  _begin,
  _end,
  _if,
  _else
};

class Operations // �����, �������� �������������� ��������
{
private:
  std::map<std::string, std::vector<int>> ops; // string - name of operation; vector<int> - priority, arity; ops - OPerationS
public:
  Operations() {// ��� ���������� �������� � �����������, ����������� ����� ����������� ������ ���� �������� � Calc � �������� ������������ � static string str_op()
    ops.emplace("*", std::vector<int>{ 2, 2 });
    ops.emplace("mod", std::vector<int>{ 2, 2 });
    ops.emplace("div", std::vector<int>{ 2, 2 });
    ops.emplace("+", std::vector<int>{ 1, 2 });
    ops.emplace("-", std::vector<int>{ 1, 2 });
    ops.emplace("(", std::vector<int>{ 0, 0 });
    ops.emplace(")", std::vector<int>{ 0, 0 });
  }

  static std::string str_op() { return std::string("*, +, -, (, ), mod, div"); }

  bool IsOperation(const std::string& elem) const { return ops.find(elem) != ops.end(); } // �������� �������� �� ������ ������� ���������, ������� ��������� � ������

  int GetPriority(const std::string& elem) { return ops[elem][0]; } // �������� ��������� � �������� ��������, �������� ������������� �� ������������� 

  int GetArity(const std::string& elem) { return ops[elem][1]; } // �������� ������� � �������� ��������, �������� ������������� �� ������������� 

  Variable Calc(const std::string& elem, Variable& left, Variable right = Variable()) {// ���������
    if (elem == "*")
      return left * right;
    if (elem == "+")
      return left + right;
    if (elem == "-")
      return left - right;
    if (elem == "mod")
      return left % right;
    if (elem == "div")
      return left / right;
  }
};

class SpecialWords
{
private:
  std::map<std::string, std::vector<int>> ops; // string - name of operation; vector<int> - priority, arity; ops - OPerationS

public:
  SpecialWords()
  {
    ops.emplace("<", std::vector<int>{ -1, -1 });
    ops.emplace(">", std::vector<int>{ -1, -1 });
    ops.emplace("<=", std::vector<int>{ -1, -1 });
    ops.emplace(">=", std::vector<int>{ -1, -1 });
    ops.emplace(":=", std::vector<int>{ -1, -1 });
  }
  void Execute(std::string operation, std::vector<std::string> arguments)
  {

  }
};

