#include <iostream>
#include "runtimeEnv.h"
#include "postfix.cpp"
//#include "hierarchyList.h"

int main()
{
  static RuntimeEnv nachOS;
  nachOS.Run();

  return 0;
}