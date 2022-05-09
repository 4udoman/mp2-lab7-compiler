#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include "Stack.h"
#define PRINT(x) std::cout << x << std::endl;

class HierarchyList 
{
private:
  struct Node {
    std::string data;
    Node* next[2];
    Node(std::string x) :data(x) { next[0] = next[1] = nullptr; }
  };
  Node* root;

  TStack<Node**> *st = nullptr;
  Node** cur = nullptr;

  void DeleteSubTree(Node* p) {
    if (p == nullptr)
      return;
    DeleteSubTree(p->next[0]);
    DeleteSubTree(p->next[1]);
    delete p;
    return;
  }
public:
  HierarchyList(std::string path) { 
    std::ifstream file;
    file.open(path);
    if (!file.is_open())
      throw - 1;
    file >> *this;
    file.close();  
  }
  void start() {
    finish();
    st = new TStack<Node**>;
    cur = &root;
  }
  void next() {
    cur = &((*cur)->next[0]);
  }
  void down() {
    st->push(cur);
    cur = &((*cur)->next[1]);
  }
  void up() {
    cur = st->tos();
    st->pop();
  }
  std::string* get() {
    if (cur == nullptr)
      throw -1;
    return &((*cur)->data);
  }
  void finish() {
    if (st != nullptr) {
      delete st;
      st = nullptr;
    }
  }

  friend std::istream& operator>>(std::istream& is, HierarchyList& l) {
    l.DeleteSubTree(l.root); l.start();
    std::size_t cur_layer, layer;
    std::string s;

    if (is.peek() != EOF) {
      std::getline(is, s);
      if (s.find_first_not_of(" ") != 0)
        throw - 1;
      l.root = new Node(s);
    }
    cur_layer = 0;

    while (is.peek() != EOF) {
      std::getline(is, s);
      if((layer=s.find_first_not_of("  \n")) != std::string::npos)
        if(layer == cur_layer) {
          (*l.cur)->next[0] = new Node(s.substr(layer));
          l.next();
        }else if (layer == cur_layer + 2) {
          (*l.cur)->next[1] = new Node(s.substr(layer));
          cur_layer = layer;
          l.down();
        }else if (layer < cur_layer && (cur_layer - layer) % 2 == 0) {
          for(int i = 0; i < (cur_layer - layer)/2; ++i)
            l.up();
          (*l.cur)->next[0] = new Node(s.substr(layer));
          l.next();
          cur_layer = layer;
        } else
          throw - 1;
    }
    l.finish();
    return is;
  }

  friend std::ostream& operator<<(std::ostream& os, HierarchyList& l) {
    l.start();
    while (true) {
      if (*l.cur != nullptr) {
        for (int i = 0; i < l.st->size(); ++i)
          std::cout << "| ";
        std::cout << *l.get() << std::endl;
        l.down();
      }else if (l.st->empty()) break;
        else {
          l.up();
          l.next();
        }
    }
    l.finish();
    return os;
  }

  ~HierarchyList() { DeleteSubTree(root); finish(); }
};
