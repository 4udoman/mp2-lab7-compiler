#pragma once
#include "exitCodes.h"
#include "postfix.h"
#include "hierarchList.h"
#include "unsortListTable.h"

class ExecutableObj
{
private:
  hierList* ls;
  UnsortListTable<std::string, int>* tableInt; // TODO
  UnsortListTable<std::string, double>* tableDouble; // TODO
  TPostfix postfix;
public:
  ExecutableObj();
  ExitCodes::CODES Execute();
  ~ExecutableObj();
};
