#include "mango.hpp"
#include "token.hpp"
#include <cstdint>
#include <iostream>
#include <string>

namespace Mango {
void error(std::wstring error, std::wstring file, std::uint32_t line) {
  std::wstring message = file;
  message += L":";
  message += std::to_wstring(line);
  message += L" | ";
  message += error;
  std::wcerr << error;
}

void error(std::wstring error) { std::wcerr << error; }

// TODO: make actually good errors
void error(Mango::TokenType type, std::wstring message) {
  if (type == TokenType::END_OF_FILE) {
    Mango::error(message + L" at end");
  } else {
    Mango::error(message);
  }
}
} // namespace Mango
