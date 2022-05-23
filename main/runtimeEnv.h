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
    int choice = 1, code = 0; 
    std::string tmp; 
    ExecObj *prog;
    HierarchyList* l;

    while (choice){
      std::cout <<
      "           ***Pascal-- Emulator***" << std::endl <<
      "Menu: " << std::endl <<
      "1 Load Program" << std::endl <<
      "2 Run Program" << std::endl <<
      "0 Exit" << std::endl <<
      "Choose Option:" << std::endl;
      std::cin >> choice;
      switch (choice) {
      case 0:
        std::cout << "Goodbye" << std::endl;
        break;
      case 1:
        std::cout << "Enter path: ";
        std::cin >> tmp;
        // l = new HierarchyList();
        // l.Build(tmp);
        // if(!(code = Check(l))) {
        //   std::cout << ExitCodes::ErrorList[code];
        //   break;
        // }
        std::cout << "Enter name: ";
        std::cin >> tmp;
        // progs.Insert(tmp, *prog);
        break;
      case 2:
        std::cout << "Enter name: ";
        std::cin >> tmp;
        if ((prog = progs.Find(tmp)) == nullptr) {
          std::cout << "No such program" << std::endl;
          break;
        }
        // frog->Run();
        break;
      default:
        std::cout << "No such command" << std::endl;
      }
    }
  }
  ~RuntimeEnv() {}
};
