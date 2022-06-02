#pragma once
#include <map>
#include <vector>
#include <iostream>
#include "variable.h"

class Operations //  ласс, хран€щий поддерживаемые операции
{
private:
  std::map<std::string, std::vector<int>> ops; // string - name of operation; vector<int> - priority, arity; ops - OPerationS
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
    ops.emplace("then", std::vector<int>{ -1, -1 });
    ops.emplace("begin", std::vector<int>{ 0, 0 });
    ops.emplace("end", std::vector<int>{ 0, 0 });
    ops.emplace("program", std::vector<int>{ -1, -1 });
    ops.emplace(";", std::vector<int>{ -1, -1 });
    ops.emplace(",", std::vector<int>{ -1, -1 });
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

  Variable* Calc(const std::string& elem, Variable left, Variable right)
  {
    if (elem == "*")
    {
      Variable var(left * right);
      return &var;
    } 
    if (elem == "+")
    {
      Variable var(left + right);
      return &var;
    }
    if (elem == "-")
    {
      Variable var(left - right);
      return &var;
    }
    if (elem == "mod")
    {
      Variable var(left % right);
      return &var;
    }
    if (elem == "div")
    {
      Variable var(left / right);
      return &var;
    }
    if (elem == "=")
    {
      Variable var(left == right);
      return &var;
    }
    if (elem == ">")
    {
      Variable var(left > right);
      return &var;
    }
    if (elem == "<")
    {
      Variable var(left < right);
      return &var;
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
