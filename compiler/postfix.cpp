#include "postfix.h"
//
bool TPostfix::BracketsCorrect(const string& str) const
{
  TStack<bool> stack; // ���� ��� �������� ������� '('
  for (const char& elem : str) {
    if (elem == '(') {
      stack.push(true);
      continue;
    }
    if (elem == ')') {
      if (stack.empty()) // ���� ���� ����, �� ��� ���� ��� ')' -> ������
        return false;
      stack.pop();
      continue;
    }
  }
  if (!stack.empty()) // ���� ���� �� ����, �� ������� ���� ')' -> ������
    return false;
  return true;
}

//������ ��� ���������� ��������� � �������, � �� ��� �������������� ����������
void TPostfix::ToInfix(const string& str)
{
  string elem;
  string copyStr(str);

  DeleteSpaces(copyStr);
  for (int i = 0; i < copyStr.size();)
  {
    string lexem;
    elem = copyStr[i];


    if (function.IsFunction(lexem))
    {
      infix.push_back(lexem);
      lexem = "";
      while (copyStr[i] != ';')
      {

      }
    }
    //if (operation.IsOperation(elem))
    //{

    //}

    //if ((lexem == "-") && (infix.size() == 0 || (infix.size() > 0 && infix[infix.size() - 1] == "("))) // ����������� �������� ������ � ��������
    //  infix.push_back("0");
    ////�������� �� ������������ ��������� ����������
    //if (lexem.find_first_of("0123456789") == 0 && lexem.find_first_not_of("0123456789.") != string::npos) {// �������� �� ������������ ����� ����������, ���� ��� ����������
    //  std::string exc = "Invalid format of variable: " + lexem;
    //  throw exc;
    //}
    //if (lexem.size() != 0)
    //  infix.push_back(lexem);
  }
}

//void TPostfix::ToPostfix()
//{
//  TStack<string> opStack;
//
//  for (int i = 0; i < infix.size(); i++) {
//    string lexem = infix[i];
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
//bool TPostfix::IsMonom(const string& lexem)
//{
//  if (lexem.find_first_of("xyz") != string::npos && lexem.find_first_not_of("xyz0123456789.") == string::npos)
//    return true;
//  return false;
//}
//
//bool TPostfix::IsNumber(const string& lexem)
//{
//  if (lexem.find_first_not_of("1234567890.") != string::npos)
//    return false;
//  return true;
//}
//
inline void TPostfix::DeleteSpaces(string& str)
{
  for (size_t i = 0; i < str.size(); i++) {
    if (str[i] == ' ')
      str.erase(i, 1);
  }
}
KeyWords TPostfix::KeyWord(const string& str)
{
  return KeyWords::begin;
}
bool TPostfix::IsFunction(const string& str)
{
  return false;
}

//����� ����������� �������, � ����� �������������� ��������
void TPostfix::Execute(HierarchyList::iterator* it)
{
  TStack<string> argumets;
  for (size_t i = 0; i < postfix.size(); i++)
  {
    switch (KeyWord(postfix[i]))
    {
    case KeyWords::program:
      it->next();
      break;
    case KeyWords::_const:
      it->down();
      break;
    case KeyWords::var:
      it->down();
      break;
    case KeyWords::begin:
      it->down();
      break;
      //����������
    case KeyWords::end:
      it->up();
      break;
    case KeyWords::_if:
      if (CalculateIf(argumets.pop()))
        it->down();
      else
        it->next();
      break;
    case KeyWords::_else:
      it->down();
      break;
    default:
      break;
    }

    //������, ������� write, read, writeln :=
    //:= ����� ��������
    //read - ����� �������
    //write - ��������������
    if (IsFunction(postfix[i]))
    {
      ////////write
      if (postfix[i] == "write")
      {
        vector<string> temp;
        while (!argumets.empty())
        {   
          temp.push_back(argumets.pop());
        }
        for (size_t j = temp.size() - 1; j >= 0; j--)
        {
          if (tableInt->Find(temp[j]) != nullptr)
          {
            cout << tableInt->Find(temp[j]);
            continue;
          }
          else if (tableDouble->Find(temp[j]) != nullptr)
          {
            cout << tableInt->Find(temp[j]);
            continue;
          }
          cout << temp[j];
        }
      }
      ////////read
      else if (postfix[i] == "read")
      {
        if (tableInt->Find(argumets.tos()) != nullptr)
        {
          int variable;
          cin >> variable;
          tableInt->changeValue(argumets.pop(), variable);
          break;
        }
        else if (tableDouble->Find(argumets.tos()) != nullptr)
        {
          double variable;
          cin >> variable;
          tableDouble->changeValue(argumets.pop(), variable);
          break;
        }
        else
          throw string("No such variable!");
      }
      ////////:=
      else if (postfix[i] == ":=")
      {
        string expression = argumets.pop();
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
          throw string("No such variable!");
      }
      ////////: ������� ����� ���������� ����, ��� ��� ���� const, ����� ��� ���������� ���������� ��������� ���.
      else if (postfix[i] == ":")
      {
        if (argumets.pop() == "integer")
        {
          //������, ���������� ��������� �������� (+3 ��� ��� ����� ��������� ���� 2 ��������)
          if (postfix[i].size() == i + 3)
          {
            string expression = postfix[++i];
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
            throw string("������ �������������!");
        }
        //���������� ���� double
        else
        {
          if (postfix[i].size() == i + 3)
          {
            string expression = postfix[++i];
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
            throw string("������ �������������!");
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
