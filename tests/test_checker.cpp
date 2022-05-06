//
//class Errors -> ExitCodes
//{
//public:
//  enum ERRORS
//  {
//    ALL_IS_GOOD = 0,
//    UNEXPECTED_ERROR
//  };
//  std::vector<std::string> ErrorList;
//  Errors()
//  {
//    ErrorList.push_back("All is good");
//    ErrorList.push_back("Unexpected error");
//  }
//  ~Errors();
//};

// test on all_is_good & unexpected_error
// несколько тестов могут быть на одну и ту же ошибку

// сам  Checker реализуется как набор функций. Сами тесты будут проверять возвращается ли правильная ошибка?