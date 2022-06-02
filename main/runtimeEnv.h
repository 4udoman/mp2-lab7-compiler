#pragma once
#include <iostream>
#include "exitCodes.h"
#include "syntChecker.h"
#include "execObj.h"
#include "unsortListTable.h"

class RuntimeEnv
{
private:
  UnsortListTable<std::string, ExecObj> progs;
public:
  RuntimeEnv() {}
  void Run() {
    int numStr = 0;
    int choice = 1;
    ExitCodes::CODES code;
    std::string tmp;
    HierarchyList* l; UnsortListTable<std::string, Variable>* t;
    ExecObj* chosen_prog;

    while (choice) {
      system("cls");
      std::cout <<
        "        _--***  Pascal-- Emulator  ***--_" << std::endl <<
        "Menu: " << std::endl <<
        "1 Load Program" << std::endl <<
        "2 Run Program" << std::endl <<
        "3 Show program list" << std::endl <<
        "0 Exit" << std::endl <<
        "Choose Option:" << std::endl;
      std::cin >> choice;
      switch (choice) {
      case 0:
        std::cout << "Goodbye" << std::endl;
        choice = 0;
        break;
      case 1:
        std::cout << "Enter path: ";
        std::cin >> tmp;
        l = new HierarchyList();
        try {
          l->Build(tmp);
        }
        catch (...) {
          // ERROR wrong tabulation
          delete l;
          break;
        }
        std::cout << *l << std::endl << std::endl;
        if (!(code = SyntChecker::Check(l, t, numStr))) {
          std::cout << code << "in " << numStr << " line\n";
          delete l;
          break;
        }
        std::cout << "Enter name: ";
        std::cin >> tmp;
        progs.Insert(tmp, ExecObj{ l, t });
        break;
      case 2:
        std::cout << "Enter name: ";
        std::cin >> tmp;
        if ((chosen_prog = progs.Find(tmp)) == nullptr) {
          std::cout << "No such program" << std::endl;
          break;
        }
        system("cls");
        chosen_prog->Execute();
        system("pause");
        break;
      case 3:
        progs.PrintKeys();
        break;
      default:
        std::cout << "No such command" << std::endl;
      }
    }
  }
  ~RuntimeEnv() {}
};
