#pragma once
#include <iostream>
#include <conio.h>
#include "exitCodes.h"
#include "syntChecker.h"
#include "execObj.h"
#include "unsortListTable.h"
#include "postfix.cpp"

class RuntimeEnv {
  UnsortListTable<std::string, ExecObj> progs;
public:
  RuntimeEnv() {}

  void Run() {
    int numStr = 0; char choice;
    ExitCodes::CODES code; std::string tmp;
    HierarchyList* l = nullptr; UnsortListTable<std::string, Variable>* t = nullptr;
    ExecObj* prog = nullptr;

    while (true) {
      system("cls");
      std::cout <<
        " _--*** Pascal-- Emulator ***--_" << std::endl <<
        "Menu: " << std::endl <<
        "1 Load Program" << std::endl <<
        "2 Run Program" << std::endl <<
        "3 Show program list" << std::endl <<
        "0 Exit" << std::endl;
      choice = _getch();
      switch (choice) {
      case '0': // EXIT
        std::cout << "Goodbye" << std::endl;
        return;
      case '1': // LOAD PROGRAM
        std::cout << "Enter path: ";
        std::cin >> tmp;
        l = new HierarchyList();
        try { l->Build(tmp); }
        catch (int line) {
          if(line == -1)
            std::cout << "No such file" << std::endl;
          else
            std::cout << ExitCodes::CODES::WRONG_TABULATION << " on line " << line << std::endl;
          delete l;
          break;
        }
        std::cout << *l << std::endl << std::endl;

        if ((code = SyntChecker::Check(l, t, numStr)) != ExitCodes::ALL_IS_GOOD) {
         std::cout << code << " on line " << numStr << std::endl;
         delete l;
         break;
        }
        std::cout << "Enter name: ";
        std::cin >> tmp;
        progs.Insert(tmp, ExecObj(l, t, true));
        break;
      case '2': // RUN PROGRAM
        std::cout << "Enter name: ";
        std::cin >> tmp;
        if ((prog = progs.Find(tmp)) == nullptr) {
          std::cout << "No such program" << std::endl;
          break;
        }
        system("cls");
        prog->Execute();
        break;
      case '3': // PRINT PROGRAMS
        std::cout << "Program list:" << std::endl;
        progs.PrintKeys();
        break;
      default:
        std::cout << "No such command" << std::endl;
      }
      std::cout << "Press any key to continue..." << std::endl;
      _getch();
    }
  }
  ~RuntimeEnv() {}
};
