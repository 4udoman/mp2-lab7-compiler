#pragma once
#include <map>
#include <vector>
#include <iostream>
#include "variable.h"

class Operations // �����, �������� �������������� ��������
{
private:
  std::map<std::string, std::vector<int>> ops;// string - name of operation; vector<int> - priority, arity; ops - OPerationS
public:
  Operations() { // ��� ���������� �������� � �����������, ����������� ����� ����������� ������ ���� �������� � Calc � �������� ������������ � static string str_op()
    ops.emplace("*", std::vector<int>{ 4, 2 });
    ops.emplace("mod", std::vector<int>{ 4, 2 });
    ops.emplace("div", std::vector<int>{ 4, 2 });
    ops.emplace("+", std::vector<int>{ 3, 2 });
    ops.emplace("-", std::vector<int>{ 3, 2 });
    ops.emplace("(", std::vector<int>{ 0, 0 });
    ops.emplace(")", std::vector<int>{ 0, 0 });

    ops.emplace(":=", std::vector<int>{ 1, 2 });
    ops.emplace("=", std::vector<int>{ 1, 2 });
    ops.emplace("<", std::vector<int>{ 1, 2 });
    ops.emplace(">", std::vector<int>{ 1, 2 });
    ops.emplace("<=", std::vector<int>{ 1, -1 });
    ops.emplace(">=", std::vector<int>{ 1, -1 });
    ops.emplace("write", std::vector<int>{ 2, -1 });
    ops.emplace("writeln", std::vector<int>{ 2, -1 });
    ops.emplace("read", std::vector<int>{ 2, -1 });
    ops.emplace("if", std::vector<int>{ 0, 1 });
    ops.emplace("begin", std::vector<int>{ 0, 0 });
    ops.emplace("end", std::vector<int>{ 0, 0 });
    ops.emplace("const", std::vector<int>{ -1, -1 });
    ops.emplace("var", std::vector<int>{ -1, -1 });
    ops.emplace("end.", std::vector<int>{ -1, -1 });
  }

  bool isOperation(const std::string& elem) const { return ops.find(elem) != ops.end(); } // �������� �������� �� ������ ������� ���������, ������� ��������� � ������

  std::string getOperation(const std::string& elem) const
  {
    if (isOperation(elem))
      return elem;
    throw std::string("");
  }

  int getPriority(const std::string& elem) { return ops[elem][0]; } // �������� ��������� � �������� ��������, �������� ������������� �� ������������� 

  int getArity(const std::string& elem) { return ops[elem][1]; } // �������� ������� � �������� ��������, �������� ������������� �� ������������� 

  Variable Calc(const std::string& elem, Variable left, Variable right)
  {
    if (elem == "*")
    {
      return Variable(left * right);
    } 
    if (elem == "+")
    {
      return Variable(left + right);
    }
    if (elem == "-")
    {
      return Variable(left - right);
    }
    if (elem == "mod")
    {
      return Variable(left % right);
    }
    if (elem == "div")
    {
      return Variable(left / right);
    }
    if (elem == "=")
    {
      return Variable(left == right);
    }
    if (elem == ">")
    {
      return Variable(left > right);
    }
    if (elem == "<")
    {
      return Variable(left < right);
    }
  }

  bool IsMathOperation(const std::string op)
  {
    if (op == "*")
      return true;
    if (op == "+")
      return true;
    if (op == "-")
      return true;
    if (op == "mod")
      return true;
    if (op == "div")
      return true;
    if (op == "=")
      return true;
    if (op == ">")
      return true;
    if (op == "<")
      return true;

    return false;
  }
};

std::vector<std::string> Parser(const std::string& str)
{
  Operations operation;
  std::vector<std::string> infix;

  for (int i = 0; i < str.size();)
  {
    std::string elem;
    std::string lexem;
    elem = str[i];

    if (operation.isOperation(elem))
    {
      lexem = (char)tolower(elem[0]);
      i++;
    }
    else
    {
      if (elem == "'") // ��� �������� �� i < str.size(), ������ ��� �������, ��� ������ ��������� ������� �� ���� �����
      {
        lexem += elem[0];
        elem = str[++i];
        while (elem != "'") // � �������� ���������� ���� �������� �������� �� i < str.size()
        {
          lexem += elem[0];
          elem = str[++i];
        }
        lexem += elem[0];
        elem = str[++i];
      }
      while (!operation.isOperation(lexem) && !operation.isOperation(elem) && i < str.size())
      {
        if (elem != " ")
          lexem += (char)tolower(elem[0]);
        elem = str[++i];
      }
    }

    if ((lexem == "-") && (infix.size() == 0 || (infix.size() > 0 && infix[infix.size() - 1] == "("))) // ����������� �������� ������ � ��������
      infix.push_back("0");

    if (lexem.size() != 0)
      infix.push_back(lexem);
  }

  return infix;
}
