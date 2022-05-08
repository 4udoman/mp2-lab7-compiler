#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include "Stack.h"

class HierarchyList 
{
private:
  struct Node {
    std::string data;
    Node* next[2];
    Node(std::string x) :data(x) { next[0] = next[1] = nullptr; }
  };
  Node* root;

  TStack<Node*> *st = nullptr;
  Node* cur = nullptr;

  void DeleteSubTree(Node* p) {
    if (p == nullptr)
      return;
    DeleteSubTree(p->next[0]);
    DeleteSubTree(p->next[1]);
    delete p;
    return;
  }
public:
  HierarchyList(std::string x = "") { root = new Node(x); }
  void start() {
    delete[] st;
    st = new TStack<Node*>;
    cur = root;
  }
  bool next() {
    cur = cur->next[0];
  }
  void down() {
    st->push(cur);
    cur = cur->next[1];
  }
  void up() {
    cur = st->tos();
    st->pop();
  }
  std::string* get() {
    if (cur == nullptr)
      return nullptr;
    return &(cur->data);
  }
  void finish() {
    delete[] st;
  }

  friend std::istream& operator>>(std::istream& is, HierarchyList& l) {
    l.DeleteSubTree(l.root); l.start();
    std::size_t cur_layer, layer;
    std::string s;

    if (is.peek() != EOF) {
      std::getline(is, s);
      if (s.find_first_not_of(" ") != 0)
        throw - 1;
      l.root->data = s;
    }
    cur_layer = 0;

    while (is.peek() != EOF) {
      std::getline(is, s);
      if((layer=s.find_last_not_of(" ")) != std::string::npos)
        if(layer == cur_layer) {
          l.cur->next[0] = new Node(s.substr(layer));
          l.next();
        }else if (layer == cur_layer + 1) {
          l.cur->next[1] = new Node(s.substr(layer));
          ++cur_layer;
          l.down();
        }else if (layer == cur_layer - 1) {
          l.up();
          l.cur->next[0] = new Node(s.substr(layer));
          l.next();
          --cur_layer;
        }
        else
          throw - 1;
    }
    delete[] l.st;
  }

  friend std::ostream& operator<<(std::ostream& os, HierarchyList& l) {
    l.start();
    while (true) {
      if (l.cur != nullptr) {
        for (int i = 0; i < l.st->size(); ++i)
          std::cout << '|';
        std::cout << *l.get() << std::endl;
        l.down();
      }else if (l.st->empty()) break;
        else {
          l.up();
          l.next();
        }
    }
    delete[] l.st;
  }

  ~HierarchyList() { DeleteSubTree(root); delete[] st; }
};
