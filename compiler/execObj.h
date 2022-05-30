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
		//идем не линейно, поэтому нужно переходить на определенные блоки, переход зависит от логики
		postfix.NewInfix(*it);
		postfix.Execute(&it);
	  }
	  catch (...)
	  {
		cout << "Error";
	  }
	}

  }
  ~ExecObj() {}
};
