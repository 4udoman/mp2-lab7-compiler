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

  void Print() {
    Node* p = root;
    TStack<Node*> s;
    while (true) {
      if (p != nullptr) {
        for (int i = 0; i < s.size(); ++i)
          std::cout << '|';
        std::cout << p->data << std::endl;
        s.push(p);
        p = p->next[0];
      }
      else if (s.empty()) break;
      else {
        p = s.tos(); s.pop();
        p = p->next[1];
      }
    }
  }

  ~hierList();
};
