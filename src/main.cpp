#include "ast_printer.hpp"
#include "expression.hpp"
#include "interpreter.hpp"
#include "parser.hpp"
#include "scanner.hpp"
#include "visitor.hpp"
#include <fstream>
#include <iostream>
#include <sstream>

int main(int argc, char *argv[]) {
  if (argc != 2) {
    std::cout << "Usage: mango [script]";
    return 65;
  }
  std::wifstream file;
  std::wstringstream contents;
  file.open(argv[1]);
  contents << file.rdbuf();
  Mango::Scanner scanner = Mango::Scanner(contents.str());
  Mango::Parser parser = Mango::Parser(scanner.scan());

  Mango::Expression *expression = parser.parse();

  Mango::Interpreter interpreter = Mango::Interpreter();

  Mango::VisitResult result = interpreter.evaluate(expression);

  Mango::Data *data = std::get<Mango::Data *>(result);

  std::cout << std::get<std::int32_t>(*data);

  delete expression;

  return 0;
}
