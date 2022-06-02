#include <iostream>
#include "runtimeEnv.h"

int main()
{
  static RuntimeEnv nachOS;
  nachOS.Run();
  /*HierarchyList* l = new HierarchyList();
  l->Build("program.txt");
  UnsortListTable<std::string, Variable>* t = new UnsortListTable<std::string, Variable>;
  Variable pi("3.14", "pi");
  t->Insert("pi", pi);
  t->Insert("numa1", Variable(0));
  t->Insert("numa2", Variable(0));
  t->Insert("res", Variable(0));
  t->Insert("d", Variable(0));

  ExecObj execObj(l, t);
  execObj.Execute(); // */

  return 0;
}