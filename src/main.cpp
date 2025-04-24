#include "scanner.hpp"
#include "token.hpp"
#include <fstream>
#include <iostream>
#include <string>

int main(int argc, char *argv[]) {
  if (argc != 2) {
    std::cout << "Usage: mango [script]";
    return 65;
  }
  std::wifstream file;
  file.open(argv[0]);
  std::string line = std::string();
  std::wstring contents = std::wstring(std::istreambuf_iterator<wchar_t>(file),
                                       std::istreambuf_iterator<wchar_t>());
  Mango::Scanner scanner = Mango::Scanner(contents);
  std::vector<Mango::Token> tokens = scanner.scan();
  return 0;
}
