#pragma once
#include <string>
#include <iostream>
#include "tree.h"

class hierList
{
  // ����� ����� ��������
private:
  Tree<std::string> lists;
  std::istream& ReadFromStream(std::istream& in);
public:
  hierList();
  void Print() { lists.Print(); }
  ~hierList();
};
