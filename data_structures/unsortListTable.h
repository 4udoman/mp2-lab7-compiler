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

  UnsortListTable<TKey, TData> operator+(const UnsortListTable<TKey, TData>& t) {
    UnsortListTable<TKey, TData> res;
    for (auto it = list.cbegin(); it != list.cend(); it++)
      res.list.InsertFirst(*it);
    for (auto it = t.list.cbegin(); it != t.list.cend(); it++)
      res.list.InsertFirst(*it);
    return res;
  }

  ~UnsortListTable() { }

};
