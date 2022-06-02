#pragma once
#include "exitCodes.h"
#include "postfix.h"
#include "hierarchyList.h"
#include "unsortListTable.h"

class ExecObj
{
private:
  HierarchyList* ls;
  UnsortListTable<std::string, Variable>* table; // TODO
  TPostfix postfix;
public:
  ExecObj(HierarchyList* _ls, UnsortListTable<std::string, Variable>* _table)
  {
    ls = _ls;
    table = _table;
    postfix.Init(_table);
  }
  
  void Execute()
  {
    auto it = ls->begin();
    while ((*it) != "end.")
    {
      try
      {
        postfix.Execute(&it); //идем не линейно, поэтому итератор может измениться
      }
      catch (std::string errorStr)
      {
        std::cout << errorStr;
      }
    }

  }

  ~ExecObj() {}
};
