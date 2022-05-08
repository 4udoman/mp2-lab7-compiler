#pragma once
#include <string>
#include <iostream>
#include "binaryTree.h"

class hierList : private BinaryTree<std::string>
{
  // ����� ����� ��������, ������������, � �� ����������
  // �������� ��� private �������������
private:
  BinaryTree<std::string> lists;
  std::istream& ReadFromStream(std::istream& in);
public:
  hierList();

  // moved to new place

  ~hierList();
};
