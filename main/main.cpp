#include <iostream>
#include "runtimeEnv.h"
#include "postfix.cpp"
//#include "hierarchyList.h"

int main()
{
 /* static RuntimeEnv nachOS;
  nachOS.Run();*/
  HierarchyList l;
  l.Build("program.txt");
  UnsortListTable<std::string, Variable> t;
  Variable pi("3.14", "pi");
  t.Insert("pi", pi);
  t.Insert("numa1", Variable(0));
  t.Insert("numa2", Variable(0));
  t.Insert("res", Variable(0));
  t.Insert("d", Variable(0));

  ExecObj execObj(&l, &t);
  execObj.Execute();

  return 0;
}