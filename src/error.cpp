#include "error.hpp"
#include "token.hpp"
#include <cstdint>
#include <iostream>
#include <string>

namespace Mango {
void report(std::int32_t line, std::wstring where, std::wstring message) {
  std::wcerr << "Line " << line << ": " << "Error" << where << ": " << message;
}

void error(std::int32_t line, std::wstring message) {
  report(line, L"", message);
}

void error(Token token, std::wstring message) {
  if (token.type == TokenType::END_OF_FILE) {
    report(token.lexeme.line, L" at the end of the file.", message);
  } else {
    report(token.lexeme.line, token.to_string(), message);
  }
}

} // namespace Mango
