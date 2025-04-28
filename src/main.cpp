#include "ast_printer.hpp"
#include "expression.hpp"
#include "scanner.hpp"
#include "token.hpp"
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
  std::vector<Mango::Token> tokens = scanner.scan();

  return 0;
}
