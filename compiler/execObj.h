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
  ExecObj() {}
  ExitCodes::CODES Execute() {}
  ~ExecObj() {}
};
