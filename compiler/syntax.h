#pragma once
#include <map>
#include <vector>
#include <iostream>
#include "variable.h"

class Operations // Класс, хранящий поддерживаемые операции
{
private:
  std::map<std::string, std::vector<int>> ops; // string - name of operation; vector<int> - priority, arity; ops - OPerationS
public:
  Operations() { // При добавлении операции в конструктор, обязательно нужно реализовать логику этой операции в Calc и добавить наименование в static string str_op()
    ops.emplace("*", std::vector<int>{ 2, 2 });
    ops.emplace("mod", std::vector<int>{ 2, 2 });
    ops.emplace("div", std::vector<int>{ 2, 2 });
    ops.emplace("+", std::vector<int>{ 1, 2 });
    ops.emplace("-", std::vector<int>{ 1, 2 });
    ops.emplace("(", std::vector<int>{ 0, 0 });
    ops.emplace(")", std::vector<int>{ 0, 0 });

    ops.emplace(":=", std::vector<int>{ -1, -1 });
    ops.emplace("=", std::vector<int>{ -1, -1 });
    ops.emplace("<", std::vector<int>{ -1, -1 });
    ops.emplace(">", std::vector<int>{ -1, -1 });
    ops.emplace("<=", std::vector<int>{ -1, -1 });
    ops.emplace(">=", std::vector<int>{ -1, -1 });
    ops.emplace("write", std::vector<int>{ -1, -1 });
    ops.emplace("writeln", std::vector<int>{ -1, -1 });
    ops.emplace("read", std::vector<int>{ -1, -1 });
    ops.emplace("if", std::vector<int>{ -1, -1 });
    ops.emplace("then", std::vector<int>{ -1, -1 });
    ops.emplace("begin", std::vector<int>{ -1, -1 });
    ops.emplace("end", std::vector<int>{ -1, -1 });
  }

  static std::string str_op() { return std::string("*, +, -, (, ), mod, div"); }

  bool isOperation(const std::string& elem) const { return ops.find(elem) != ops.end(); } // Проверка является ли данный элемент операцией, которая объявлена в классе

  std::string getOperation(const std::string& elem) const
  {
    if (isOperation(elem))
      return elem;
    throw std::string("");
  }

  int getPriority(const std::string& elem) { return ops[elem][0]; } // Получить приоритет у заданной операции, контроль использования за программистом 

  int getArity(const std::string& elem) { return ops[elem][1]; } // Получить арность у заданной операции, контроль использования за программистом 

  Variable Calc(const std::string& elem, Variable left, Variable right = Variable()) {// Вычислить
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
