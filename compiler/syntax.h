#pragma once
#include <algorithm>
#include <list>
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
    ops.emplace(":", std::vector<int>{ 0, 0 });
    ops.emplace("=", std::vector<int>{ 1, 2 });
    ops.emplace("<", std::vector<int>{ 1, 2 });
    ops.emplace(">", std::vector<int>{ 1, 2 });
    ops.emplace("<=", std::vector<int>{ 1, -1 });
    ops.emplace(">=", std::vector<int>{ 1, -1 });
    ops.emplace("write", std::vector<int>{ 2, -1 });
    ops.emplace("writeln", std::vector<int>{ 2, -1 });
    ops.emplace("read", std::vector<int>{ 2, -1 });
    ops.emplace("if", std::vector<int>{ 0, 1 });
    ops.emplace("else", std::vector<int>{ 0, 1 });
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

class Syntax
{
private:
  std::list<std::string> synt;
public:
  Syntax()
  {
    synt.push_front("*");
    synt.push_front("+");
    synt.push_front("-");
    synt.push_front("(");
    synt.push_front(")");
    synt.push_front("mod");
    synt.push_front("div");
    synt.push_front(":=");
    synt.push_front("=");
    synt.push_front("<");
    synt.push_front(">");
    synt.push_front(">=");
    synt.push_front("<=");
    synt.push_front("write");
    synt.push_front("writeln");
    synt.push_front("read");
    synt.push_front("if");
    synt.push_front("then");
    synt.push_front("else");
    synt.push_front("begin");
    synt.push_front("end");
    synt.push_front("end.");
    synt.push_front("program");
    synt.push_front("const");
    synt.push_front("var");
    synt.push_front(":");
    synt.push_front(";");
    synt.push_front(",");
  }

  bool isSyntax(const std::string& elem) const { return std::find(synt.begin(), synt.end(), elem) != synt.end(); }
};

std::vector<std::string> Parser(const std::string& str)
{
  Syntax syntax;
  std::vector<std::string> infix;

  for (int i = 0; i < str.size();)
  {
    std::string elem;
    std::string lexem;
    elem = str[i];

    if (syntax.isSyntax(elem))
    {
      lexem = (char)tolower(elem[0]);
      i++;
    }
    else
    {
      if (elem == "'" && i < str.size())
      {
        do
        {
          lexem += elem[0];
          elem = str[++i];
        } while (elem != "'" && i < str.size());
        lexem += elem[0];
        elem = str[++i];
      }
      while (!syntax.isSyntax(lexem) && !syntax.isSyntax(elem) && i < str.size())
      {
        if (elem != " ")
          lexem += (char)tolower(elem[0]);
        elem = str[++i];
      }
    }

    if (lexem == ":" && i < str.size())
      if (str[i] == '=')
        lexem += str[i++];

    if (str.find("writeln") != std::string::npos && str.find("write") == str.find(lexem))
    {
      lexem = "writeln";
      i += 2;
      continue;
    }

    size_t pos = std::min(lexem.find("mod"), lexem.find("div"));
    if (pos != std::string::npos)
    {
      infix.push_back(lexem.substr(0, pos));
      infix.push_back(lexem.substr(pos, 3));
      infix.push_back(lexem.substr(pos + 3));
      continue;
    }

    if ((lexem == "-") && (infix.size() == 0 || (infix.size() > 0 && infix[infix.size() - 1] == "("))) // ѕревращение унарного минуса в бинарный
      infix.push_back("0");

    if (lexem.size() != 0)
      infix.push_back(lexem);
  }

  return infix;
}
