#include <iostream>
#include "runtimeEnv.h"

int main()
{
  //static RuntimeEnv nachOS;
  //nachOS.Run();
  HierarchyList l;
  l.Build("program.txt");
  std::cout << l << std::endl;
  return 0;
}