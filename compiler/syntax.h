#pragma once
#include <map>
#include <vector>
#include <iostream>
#include "variable.h"

class Operations //  ласс, хран€щий поддерживаемые операции
{
private:
  std::map<std::string, std::vector<int>> ops;// string - name of operation; vector<int> - priority, arity; ops - OPerationS
public:
  Operations() { // ѕри добавлении операции в конструктор, об€зательно нужно реализовать логику этой операции в Calc и добавить наименование в static string str_op()
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

  bool isOperation(const std::string& elem) const { return ops.find(elem) != ops.end(); } // ѕроверка €вл€етс€ ли данный элемент операцией, котора€ объ€влена в классе

  std::string getOperation(const std::string& elem) const
  {
    if (isOperation(elem))
      return elem;
    throw std::string("");
  }

  int getPriority(const std::string& elem) { return ops[elem][0]; } // ѕолучить приоритет у заданной операции, контроль использовани€ за программистом 

  int getArity(const std::string& elem) { return ops[elem][1]; } // ѕолучить арность у заданной операции, контроль использовани€ за программистом 

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
      if (elem == "'") // Ќет проверки на i < str.size(), потому что считаем, что строка правильно введена на этом этапе
      {
        lexem += elem[0];
        elem = str[++i];
        while (elem != "'") // ¬ проверке синтаксиса сюда добавить проверку на i < str.size()
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

    if ((lexem == "-") && (infix.size() == 0 || (infix.size() > 0 && infix[infix.size() - 1] == "("))) // ѕревращение унарного минуса в бинарный
      infix.push_back("0");

    if (lexem.size() != 0)
      infix.push_back(lexem);
  }

  return infix;
}
