#pragma once
#include <iostream>
#include "Stack.h"

template <class T>
class BinaryTree 
{
protected:
  struct Node {
    T data;
    Node* next[2];
    Node() { data = T();  next[0] = next[1] = nullptr; }
    Node(T x) :data(x) { next[0] = next[1] = nullptr; }
  };
  Node* root;
  void DeleteSubTree(Node* p) {
    if (p == nullptr)
      return;
    DeleteSubTree(p->next[0]);
    DeleteSubTree(p->next[1]);
    delete p;
    return;
  }
public:
  class iterator;
  BinaryTree() { root = new Node();  }
  void Insert(iterator it, int i, T x) {
    if (it.cur->next[i] == nullptr) {
      it.cur->next[i] = new Node(x);
    }
  }

  ~BinaryTree() { DeleteSubTree(root); }

  iterator begin() { return iterator(root); }

  class iterator {
    Node* cur;
  public:
    friend BinaryTree;
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
