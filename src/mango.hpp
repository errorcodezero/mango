#include "token.hpp"
#include <cstdint>
#include <string>

namespace Mango {
void error(std::wstring error, std::wstring file, std::uint32_t line);
void error(TokenType type, std::wstring message);
void error(std::wstring error);
} // namespace Mango
