#include "token.hpp"
#include <cstdint>
#include <string>

namespace Mango {
void error(std::int32_t line, std::wstring message);
void report(std::int32_t line, std::wstring where, std::wstring message);
} // namespace Mango
