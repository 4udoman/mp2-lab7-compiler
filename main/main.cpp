#include <iostream>
#include "runtimeEnv.h"

int main()
{
  //static RuntimeEnv nachOS;
  //nachOS.Run();
  HierarchyList l;
  l.Build("program.txt");
  std::cout << l << std::endl;
  UnsortListTable<std::string, Variable> t;
  ExecObj execObj(&l, &t);
  execObj.Execute();
  return 0;
}