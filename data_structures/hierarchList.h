#pragma once
#include <string>
#include <iostream>
#include "tree.h"

class hierList : private Tree<std::string>
{
  // Здесь будет итератор, перевызывать, а не копировать
  // Подумать над private наследованием
private:
  Tree<std::string> lists;
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
