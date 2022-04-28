#include <iostream>
#include "Tree.h"
using namespace std;

int main()
{
  Tree<int> t;
  auto it = t.begin();
  t.Insert(it, 1, -1);
  t.Insert(it, 0, 1);
  it.GoTo(0);
  t.Insert(it, 1, -2);
  t.Insert(it, 0, 2);
  t.Print();


  return 0;
}