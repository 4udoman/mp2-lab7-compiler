#pragma once
#include <iostream>
#include "Stack.h"

template <class T>
class Tree {
  struct Node {
    T data;
    Node* next[2];
    Node() { data = T();  next[0] = next[1] = nullptr; }
    Node(T x) :data(x) { next[0] = next[1] = nullptr; }
  };
  Node* root;
  void DeleteNode(Node* p) {
    if (p == nullptr)
      return;
    DeleteNode(p->next[0]);
    DeleteNode(p->next[1]);
    delete p;
    return;
  }
public:
  class iterator;
  Tree() { root = new Node();  }
  void Insert(iterator it, int i, T x) {
    if (it.cur->next[i] == nullptr) {
      it.cur->next[i] = new Node(x);
    }
  }
  void Print() {
    Node* p = root;
    TStack<Node*> s;
    while (true) {
      if (p != nullptr) {
        for (int i = 0; i < s.size(); ++i)
          std::cout << ' ';
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
  ~Tree() {
    DeleteNode(root);
  }

  iterator begin() { return iterator(root); }

  class iterator {
    Node* cur;
  public:
    friend Tree;
    iterator() :cur(nullptr) {};
    iterator(Node* i) : cur(i) {};
    iterator(const iterator& i) { cur = i.cur; }
    iterator& operator=(const iterator& i) {
      cur = i.cur;
      return *this;
    }
    T& operator*() const { return cur->data; }
    T* operator->() const { return &(cur->data); }
    bool operator!=(const iterator& i) const { return cur != i.cur; }
    bool operator==(const iterator& i) const { return cur == i.cur; }
    bool end(int i) { return cur->next[i] == nullptr; }
    const iterator& GoTo(int i) { cur = cur->next[i]; return *this; }
  };
};
