#include "expression.hpp"
#include "parser.hpp"
#include "scanner.hpp"
#include <fstream>
#include <iostream>
#include <sstream>

int main(int argc, char *argv[]) {
  if (argc != 2) {
    std::wcout << L"Usage: mango [script]";
    return 65;
  }
  std::wifstream file;
  std::wstringstream contents;
  file.open(argv[1]);
  contents << file.rdbuf();
  Mango::Scanner scanner = Mango::Scanner(contents.str());
  Mango::Parser parser = Mango::Parser(scanner.scan());

  Mango::Expression *expression = parser.parse();

  expression->print();
  expression->interpret();

  delete expression;

  return 0;
}
