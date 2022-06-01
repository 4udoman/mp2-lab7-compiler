#include "postfix.h"
#include "syntax.h"


//Инфикс для логических выражений и функций, а не для алгебраических вычислений
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

    if ((lexem == "-") && (infix.size() == 0 || (infix.size() > 0 && infix[infix.size() - 1] == "("))) // Превращение унарного минуса в бинарный
      infix.push_back("0");

    if (lexem.size() != 0)
      infix.push_back(lexem);
  }
}

void TPostfix::ToPostfix()
{
  TStack<std::string> opStack;
  
    for (int i = 0; i < infix.size(); i++) {
      std::string lexem = infix[i];
      if (!operation.isOperation(lexem)) {
        //перед нами лексема
        if (lexem == "," || ";")
          continue;
        postfix.push_back(lexem);
        continue;
      }
      else {
        if (lexem == "(") {
          opStack.push(lexem);
          continue;
        }
  
        if (lexem == ")") {
          //Заполняем постфикс всеми лексемами между ()
          while (opStack.tos() != "(")
            postfix.push_back(opStack.pop());
          opStack.pop();
          continue;
        }
        //Пока на вершине стека находится операция с большим приоритетом, чем текущая добавляем в постфикс
        while (!opStack.empty() && operation.getPriority(opStack.tos()) >= operation.getPriority(lexem))
          postfix.push_back(opStack.pop());
  
        if (opStack.empty()) {
          opStack.push(lexem);
          continue;
        }
        else {
          if (operation.getPriority(opStack.tos()) < operation.getPriority(lexem)) {
            opStack.push(lexem);
            continue;
          }
        }
      }
    }
    while (!opStack.empty())
      postfix.push_back(opStack.pop());
}

bool TPostfix::IsNumber(const std::string& lexem)
{
  if (lexem.find_first_not_of("0123456789") != std::string::npos)
    return false;
  return true;
}

//void TPostfix::ToPostfix()
//{
//  TStack<string> opStack;
//
//  for (int i = 0; i < infix.size(); i++) {
//    std::string lexem = infix[i];
//    if (!operation.IsOperation(lexem)) {
//      //перед нами лексема
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
//        //Заполняем постфикс всеми лексемами между ()
//        while (opStack.tos() != "(")
//          postfix.push_back(opStack.pop());
//        opStack.pop();
//        continue;
//      }
//      //Пока на вершине стека находится операция с большим приоритетом, чем текущая добавляем в постфикс
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

//Здесь выполняются функции, а также переставляется итератор
void TPostfix::Execute(HierarchyList::iterator* it)
{
  if (!it) //nullptr
  {
    it->up();
    lastCompare = logicBlock.pop();
    it->next();
  }
  TStack<Variable*> algArguments;
  TStack<std::string> strArguments;
  infix.clear();
  ToInfix(**it);
  postfix.clear();
  ToPostfix();


  // Добавить вызов ToPostfix
  // Полагаю, что можно удалить следующие части проги:
  // std::vector<std::string> infix - получать его только при вызове toPostfix()
  // std::string GetStringInfix() - нет смысла выводить текущий инфикс, мы храним его в иерарх. списке


  for (size_t i = 0; i < postfix.size(); i++)
  {
    std::string tmp = postfix[i];
    if (tmp == "program")
    {
      it->next();
      break;
    }
    else if (tmp == "const")
    {
      UpdateTable(*it);
      it->next();
      break;
    }
    else if (tmp == "var")
    {
      UpdateTable(*it);
      it->next();
      break;
    }
    else if (tmp == "begin")
    {
      it->down();
      break;
    }
    else if (tmp == "end")
    {
      it->next();
      break;
    }
    else if (tmp == "if")
    {
      if (algArguments.pop()->val.i)
      {
        logicBlock.push(true);
        it->down();
        if (!it) // it == nullptr Вывод о том, что есть begin
        {
          it->next(); //перейдем в begin
        }
      }
      else
      {
        logicBlock.push(false);
        if (!it) // it == nullptr Вывод о том, что есть begin
        {
          it->Next(2); //пропускаем begin
        }
        else
          it->next();
      }
    }
    else if (tmp == "else")
    {
      if (lastCompare == false)
      {
        it->down();
        if (!it) // it == nullptr Вывод о том, что есть begin
        {
          it->next(); //перейдем в begin
        }
      }
    }
    else if (tmp == "write")
    {
      //чтобы не заниматься такой дичью, проще перегрузить оператор вывода для variable.
      if (strArguments.empty())
      {
        if (algArguments.empty())
          throw std::string("Недостаточно аргументов для вызова функции!");
        std::cout << algArguments.pop();
      }   
      else
      {
        std::cout << strArguments.pop();
        if (algArguments.empty())
          continue;
        else
        {
          std::cout << algArguments.pop();
        }
      }        
    }
    else if (tmp == "writeln")
    {
      if (strArguments.empty())
      {
        if (algArguments.empty())
          throw std::string("Недостаточно аргументов для вызова функции!");
        std::cout << *algArguments.pop();
      }
      else
      {
        std::cout << strArguments.pop();
        if (algArguments.empty())
        {
          std::cout << std::endl;
          continue;
        }
        else
        {
          std::cout << *algArguments.pop();
        }
        std::cout << std::endl;
      }
    }
    else if (tmp == "read")
    {
      Variable* v = algArguments.pop();
      std::cin >> *v;
    }
    else if (tmp == ":=")
    {
      Variable* right = algArguments.pop();
      Variable left = algArguments.pop();
      *right = left;
    }
    //строковый аргмент внутри write
    else if (tmp[0] == '\'')
    {
      int j = 1;
      std::string str;
      while (tmp[j] != '\'')
      {
        str += tmp[j];
        j++;
      }
      strArguments.push(str);
      continue;
    }
    else if (operation.IsMathOperation(tmp))
    {
      Variable right = algArguments.pop();
      Variable left = algArguments.pop();
      algArguments.push(operation.Calc(tmp, left, right));
    }
    //если ничего из этого, то это переменная либо число
    else
    {
      if (IsNumber(tmp))
      {
        Variable var(tmp);
        algArguments.push(&var);
      }
      //значит, переменная
      else
      {
        Variable* variable = table->Find(tmp);
        if (variable == nullptr)
          throw std::string("No such variable!");
        algArguments.push(variable);
      }
    }
  } 
}
 
void TPostfix::UpdateTable(HierarchyList::iterator it)
{
  //Должен работать до тех пор, пока не конец блока
  while (!it)
  {
    infix.clear();
    postfix.clear();
    ToInfix(*it);
    ToPostfix();
    TStack<std::string> lexems;
    TStack<Variable> algArguments;
    for (size_t i = 0; i < postfix.size(); i++)
    {
      if (IsNumber(postfix[i]))
      {
        algArguments.push(Variable(postfix[i]));
        continue;
      }
      else if (postfix[i] == ":")
      {
        std::string type = lexems.pop();
        if (type == "int")
        {
          if (algArguments.empty())
          {
            while (!lexems.empty())
              table->changeValue(lexems.pop(), Variable(INT_MAX));
          }
          else
          {
            Variable value(algArguments.pop());
            while (!lexems.empty())
              table->changeValue(lexems.pop(), value);
          }
        }
        else if (type == "double")
        {
          if (algArguments.empty())
          {
            while (!lexems.empty())
              table->changeValue(lexems.pop(), Variable(DBL_MAX));
          }
          else
          {
            Variable value(algArguments.pop());
            while (!lexems.empty())
              table->changeValue(lexems.pop(), value);
          }
        }
        else
          throw std::string("Unexpected type");
      }
      else if (postfix[i] == "=")
        continue;
      else
        lexems.push(postfix[i]);
    }
    it.next();
  }
}


//
//Polinom TPostfix::Calculate()
//{
//  TStack<Polinom> result;
//  for (size_t i = 0; i < postfix.size(); i++) {
//    if (operation.IsOperation(postfix[i])) {//лексема операция
//      if (operation.GetArity(postfix[i]) == 1) {
//        result.push(operation.Calc(postfix[i], result.pop(), result.pop()));
//      }
//      else if (operation.GetArity(postfix[i]) == 2) {
//        result.push(operation.Calc(postfix[i], result.pop(), result.pop()));
//      }
//
//    }
//    else if (IsMonom(postfix[i]) || IsNumber(postfix[i])) { //лексема моном или число
//      result.push(Polinom(postfix[i]));
//    }
//    else {//переменная
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
