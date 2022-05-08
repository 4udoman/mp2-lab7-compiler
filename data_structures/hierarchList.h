#pragma once
#include <string>
#include <iostream>
#include "binaryTree.h"

class hierList : private BinaryTree<std::string>
{
  // Здесь будет итератор, перевызывать, а не копировать
  // Подумать над private наследованием
private:
  BinaryTree<std::string> lists;
  std::istream& ReadFromStream(std::istream& in);
public:
  hierList();

  // moved to new place

  ~hierList();
};
