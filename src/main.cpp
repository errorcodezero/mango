#include "expression.hpp"
#include "interpreter.hpp"
#include "parser.hpp"
#include "scanner.hpp"
#include "statement.hpp"
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

  std::vector<Mango::Statement *> statements = parser.parse();
  Mango::Interpreter interpreter = Mango::Interpreter();

  interpreter.interpret(statements);

  return 0;
}
