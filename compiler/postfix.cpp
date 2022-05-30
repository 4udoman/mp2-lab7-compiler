#include "postfix.h"
#include "syntax.h"

//������ ��� ���������� ��������� � �������, � �� ��� �������������� ����������
void TPostfix::ToInfix(const std::string& str)
{
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
      while (!operation.isOperation(elem) && i < str.size())
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
}

//void TPostfix::ToPostfix()
//{
//  TStack<string> opStack;
//
//  for (int i = 0; i < infix.size(); i++) {
//    std::string lexem = infix[i];
//    if (!operation.IsOperation(lexem)) {
//      //����� ���� �������
//      postfix.push_back(lexem);
//      continue;
//    }
//    else {
//      if (lexem == "(") {
//        opStack.push(lexem);
//        continue;
//      }
//
//      if (lexem == ")") {
//        //��������� �������� ����� ��������� ����� ()
//        while (opStack.tos() != "(")
//          postfix.push_back(opStack.pop());
//        opStack.pop();
//        continue;
//      }
//      //���� �� ������� ����� ��������� �������� � ������� �����������, ��� ������� ��������� � ��������
//      while (!opStack.empty() && operation.GetPriority(opStack.tos()) >= operation.GetPriority(lexem))
//        postfix.push_back(opStack.pop());
//
//      if (opStack.empty()) {
//        opStack.push(lexem);
//        continue;
//      }
//      else {
//        if (operation.GetPriority(opStack.tos()) < operation.GetPriority(lexem)) {
//          opStack.push(lexem);
//          continue;
//        }
//      }
//    }
//  }
//  while (!opStack.empty())
//    postfix.push_back(opStack.pop());
//}
//
//bool TPostfix::IsNumber(const std::string& lexem)
//{
//  if (lexem.find_first_not_of("1234567890.") != std::string::npos)
//    return false;
//  return true;
//}
//

bool TPostfix::isFunction(const std::string& str)
{
  return false;
}

//����� ����������� �������, � ����� �������������� ��������
void TPostfix::Execute(HierarchyList::iterator* it)
{
  TStack<std::string> argumets;




  // �������� ����� ToPostfix
  // �������, ��� ����� ������� ��������� ����� �����:
  // std::vector<std::string> infix - �������� ��� ������ ��� ������ toPostfix()
  // std::string GetStringInfix() - ��� ������ �������� ������� ������, �� ������ ��� � ������. ������





  for (size_t i = 0; i < postfix.size(); i++)
  {
    std::string tmp = postfix[i];
    if (tmp == "program")
    {
      it->next();
    }
    else if (tmp == "const")
    {
      it->down();
    }
    else if (tmp == "var")
    {
      it->down();
    }
    else if (tmp == "begin")
    {
      it->down();
    }
    else if (tmp == "end")
    {
      it->up();
      it->next();
    }
    else if (tmp == "if")
    {
      if (CalculateIf(argumets.pop()))
        it->down();
      else
        it->next();
      break;
    }
    else if (tmp == "else")
    {
      it->down();
      break;
    }
  }

  //������, ������� write, read, writeln :=
  //:= ����� ��������
  //read - ����� �������
  //write - ��������������
  if (isFunction(postfix[i]))
  {
    ////////write
    if (postfix[i] == "write")
    {
      std::vector<std::string> temp;
      while (!argumets.empty())
      {
        temp.push_back(argumets.pop());
      }
      for (size_t j = temp.size() - 1; j >= 0; j--)
      {
        if (tableInt->Find(temp[j]) != nullptr)
        {
          std::cout << tableInt->Find(temp[j]);
          continue;
        }
        else if (tableDouble->Find(temp[j]) != nullptr)
        {
          std::cout << tableInt->Find(temp[j]);
          continue;
        }
        std::cout << temp[j];
      }
    }
    ////////read
    else if (postfix[i] == "read")
    {
      if (tableInt->Find(argumets.tos()) != nullptr)
      {
        int variable;
        std::cin >> variable;
        tableInt->changeValue(argumets.pop(), variable);
        break;
      }
      else if (tableDouble->Find(argumets.tos()) != nullptr)
      {
        double variable;
        std::cin >> variable;
        tableDouble->changeValue(argumets.pop(), variable);
        break;
      }
      else
        throw std::string("No such variable!");
    }
    ////////:=
    else if (postfix[i] == ":=")
    {
      std::string expression = argumets.pop();
      if (tableInt->Find(argumets.tos()) != nullptr)
      {
        int variable = *this->CalculateInt(expression);
        tableInt->changeValue(argumets.pop(), variable);
        break;
      }
      else if (tableDouble->Find(argumets.tos()) != nullptr)
      {
        double variable = *this->CalculateDouble(expression);
        tableDouble->changeValue(argumets.pop(), variable);
        break;
      }
      else
        throw std::string("No such variable!");
    }
    ////////: ������� ����� ���������� ����, ��� ��� ���� const, ����� ��� ���������� ���������� ��������� ���.
    else if (postfix[i] == ":")
    {
      if (argumets.pop() == "integer")
      {
        //������, ���������� ��������� �������� (+3 ��� ��� ����� ��������� ���� 2 ��������)
        if (postfix[i].size() == i + 3)
        {
          std::string expression = postfix[++i];
          int variable = *this->CalculateInt(expression);
          while (!argumets.empty())
          {
            tableInt->Insert(argumets.pop(), variable);
          }
        }
        //���������� �� ��������� ��������
        else if (postfix[i].size() == i + 1)
        {
          while (!argumets.empty())
          {
            tableInt->Insert(argumets.pop(), 0);
          }
        }
        else
          throw std::string("������ �������������!");
      }
      //���������� ���� double
      else
      {
        if (postfix[i].size() == i + 3)
        {
          std::string expression = postfix[++i];
          double variable = *this->CalculateDouble(expression);
          while (!argumets.empty())
          {
            tableDouble->Insert(argumets.pop(), variable);
          }
        }
        //���������� �� ��������� ��������
        else if (postfix[i].size() == i + 1)
        {
          while (!argumets.empty())
          {
            tableDouble->Insert(argumets.pop(), 0.0);
          }
        }
        else
          throw std::string("������ �������������!");
      }
    }
  }
  //������, ����������, ������ �� � ����
  argumets.push(postfix[i]);
}
}

//
//Polinom TPostfix::Calculate()
//{
//  TStack<Polinom> result;
//  for (size_t i = 0; i < postfix.size(); i++) {
//    if (operation.IsOperation(postfix[i])) {//������� ��������
//      if (operation.GetArity(postfix[i]) == 1) {
//        result.push(operation.Calc(postfix[i], result.pop(), result.pop()));
//      }
//      else if (operation.GetArity(postfix[i]) == 2) {
//        result.push(operation.Calc(postfix[i], result.pop(), result.pop()));
//      }
//
//    }
//    else if (IsMonom(postfix[i]) || IsNumber(postfix[i])) { //������� ����� ��� �����
//      result.push(Polinom(postfix[i]));
//    }
//    else {//����������
//      auto p = tableManager->Find(postfix[i]);
//      if (p == nullptr) {
//        std::string exc = postfix[i] + " was not found";
//        throw exc;
//      }
//      result.push(p->get()->getPol());
//    }
//  }
//  return result.pop();
//}
