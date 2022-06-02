#include <iostream>
#include "runtimeEnv.h"
#include "postfix.cpp"
//#include "hierarchyList.h"

int main()
{
  //static RuntimeEnv nachOS;
  //nachOS.Run();
  HierarchyList l;
  l.Build("program.txt");
  //std::cout << l << std::endl;
  UnsortListTable<std::string, Variable> t;
  Variable pi("3.14");
  t.Insert("pi", pi);

  ExecObj execObj(&l, &t);
  execObj.Execute();

  return 0;
}