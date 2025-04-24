#include "mango.hpp"
#include <cstdint>
#include <iostream>
#include <string>

void Mango::error(std::string error, std::string file, std::uint32_t line) {
  std::cerr << (file + ":" + std::to_string(line) + " | " + error);
}
