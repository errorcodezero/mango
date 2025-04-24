#include "mango.hpp"
#include <cstdint>
#include <iostream>
#include <string>

void Mango::error(std::wstring error, std::wstring file, std::uint32_t line) {
  std::wstring message = file;
  message += L":";
  message += std::to_wstring(line);
  message += L" | ";
  message += error;
  std::wcerr << error;
}
