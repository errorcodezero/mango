#include "error.hpp"
#include <cstdint>
#include <iostream>
#include <string>

namespace Mango {
void report(std::int32_t line, std::wstring where, std::wstring message) {
  std::wcout << "Line " << line << ": " << "Error" << where << ": " << message;
}

void error(std::int32_t line, std::wstring message) {
  report(line, L"", message);
}

} // namespace Mango
