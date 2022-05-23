#pragma once
#include <iostream>
#include <string.h>
#include "list.h"

template<class TKey, class TData>
class UnsortListTable{
private:
  struct Cell {
    TKey key;
    TData data;
  };
  TList<Cell> list;

public:
  UnsortListTable() {}

  void changeValue(TKey key, TData data) 
  {
    TData* p = Find(key);
    if (p == nullptr)
      return;
    *p = data;
  }

  void Insert(TKey key, TData data) {
    list.InsertFirst(Cell(key, data));
  }

  TData* Find(TKey key) {
    for (auto it = list.begin(); it != list.end(); ++it)
      if (it->key == key)
        return &(it->data);
    return nullptr;
  }

  void Delete(TKey key) {
    for (auto it = list.begin(); it != list.end(); ++it)
      if (it->key == key)
        list.Delete(it);
  }

  void PrintKeys() {
    for (auto it = list.cbegin(); it != list.cend(); ++it)
      std::cout << it->key << std::endl;
  }

  ~UnsortListTable() { }

};
