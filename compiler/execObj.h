#pragma once
#include "exitCodes.h"
#include "postfix.h"
#include "hierarchyList.h"
#include "unsortListTable.h"

class ExecObj
{
private:
  HierarchyList* ls;
  UnsortListTable<std::string, int>* tableInt; // TODO
  UnsortListTable<std::string, double>* tableDouble; // TODO
  TPostfix postfix;
public:
  ExecObj(HierarchyList* _ls, UnsortListTable<std::string, int>* _tableInt,
    UnsortListTable<std::string, double>* _tableDouble)
  {
    ls = _ls;
    tableInt = _tableInt;
    tableDouble = _tableDouble;
    postfix.Init(tableInt, tableDouble);

  }

  ExitCodes::CODES Execute()
  {
    auto it = ls->begin();
    while ((*it) != "end.")
    {
      try
      {
        postfix.NewInfix(*it);
        postfix.Execute(&it); //идем не линейно, поэтому итератор может измениться
      }
      catch (...)
      {
        std::cout << "Error";
      }
    }

  }
  ~ExecObj() {}
};
