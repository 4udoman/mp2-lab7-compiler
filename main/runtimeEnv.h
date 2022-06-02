#pragma once
#include <iostream>
#include "exitCodes.h"
#include "syntChecker.h"
#include "execObj.h"
#include "unsortListTable.h"

class RuntimeEnv {
  UnsortListTable<std::string, ExecObj> progs;
public:
  RuntimeEnv() {}

  void Run() {
    int numStr = 0, choice = 0;
    ExitCodes::CODES code; std::string tmp;
    HierarchyList* l = nullptr; UnsortListTable<std::string, Variable>* t = nullptr;
    ExecObj* chosen_prog = nullptr;

    while (true) {
      system("cls");
      std::cout <<
        " _--*** Pascal— Emulator ***--_" << std::endl <<
        "Menu: " << std::endl <<
        "1 Load Program" << std::endl <<
        "2 Run Program" << std::endl <<
        "3 Show program list" << std::endl <<
        "0 Exit" << std::endl <<
        "Choose Option:" << std::endl;
      std::cin >> choice;
      switch (choice) {
      case 0: // EXIT
        std::cout << "Goodbye" << std::endl;
        return;
      case 1: // LOAD PROGRAM
        std::cout << "Enter path: ";
        std::cin >> tmp;
        l = new HierarchyList();
        try { l->Build(tmp); }
        catch (...) {
          // ERROR wrong tabulation
          delete l;
          break;
        }
        std::cout << *l << std::endl << std::endl;

        //if (!(code = SyntChecker::Check(l, t, numStr))) {
        // std::cout << code << " on line " << numStr << std::endl;
        // delete l;
        // break;
        //}
        std::cout << "Enter name: ";
        std::cin >> tmp;
        progs.Insert(tmp, ExecObj{ l, t });
        system("pause");
        break;
      case 2: // RUN PROGRAM
        std::cout << "Enter name: ";
        std::cin >> tmp;
        if ((chosen_prog = progs.Find(tmp)) == nullptr) {
          std::cout << "No such program" << std::endl;
          break;
        }
        system("cls");
        //chosen_prog->Execute();
        system("pause");
        break;
      case 3: // PRINT PROGRAMS
        std::cout << "Program list:" << std::endl;
        progs.PrintKeys();
        system("pause");
        break;
      default:
        std::cout << "No such command" << std::endl;
      }
    }
  }
  ~RuntimeEnv() {}
};
