#pragma once
#include <string>
#include <iostream>
#include "tree.h"

class hierList
{
  // Здесь будет итератор, перевызывать, а не копировать
  // Подумать над private наследованием
private:
  Tree<std::string> lists;
  std::istream& ReadFromStream(std::istream& in);
public:
  hierList();
  void Print() { lists.Print(); }
  ~hierList();
};
