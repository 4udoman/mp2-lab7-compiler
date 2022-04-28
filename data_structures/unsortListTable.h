#pragma once
#include <string.h>
#include "list.h"

template <class TKey, class TData>
class TTable {
public:
  virtual void Insert(TData) = 0;
  virtual TData* Find(TKey) = 0;
  virtual void Delete(TKey) = 0;
  virtual void Print() = 0;
  virtual ~TTable() = 0 { }
};

template<class TKey, class TData>
class UnsortListTable final : public TTable<TKey, TData> {
private:
  TList<TData> list;

public:
  UnsortListTable() {}

  void changeValue(TKey key, TData data) ////////////////////////////////////////////////
  {
    TData* p = Find(key);
    if (p == nullptr)
      return;
    *p = data;
  }

  void Insert(TData data) override {
    list.InsertFirst(data);
  }

  TData* Find(TKey name) override {
    for (auto it = list.begin(); it != list.end(); ++it)
      if (*it == name)
        return &(*it);
    return nullptr;
  }

  void Delete(TKey name) override {
    for (auto it = list.begin(); it != list.end(); ++it)
      if (*it == name)
        list.Delete(it);
  }

  void Print() override {
    for (auto it = list.cbegin(); it != list.cend(); ++it)
      std::cout << *it << std::endl;
  }

  ~UnsortListTable() { }

};
