#ifndef INCLUDE_SRC_SCANNER_HPP_
#define INCLUDE_SRC_SCANNER_HPP_

#include "token.hpp"
#include <cstdint>
#include <optional>
#include <string>
#include <vector>

namespace Mango {
class Scanner {
private:
  const std::wstring source = std::wstring();
  std::vector<Token> tokens = std::vector<Token>();
  std::uint32_t current = 0;
  std::uint32_t line = 0;

  std::optional<wchar_t> advance();
  std::optional<wchar_t> peek();

  void push_token(const TokenType type);
  void push_token(const TokenType type, const Lexeme lexeme);
  void match_push_token(wchar_t expected, const TokenType type,
                        const TokenType fallback_type);

  bool match(const wchar_t expected);
  bool at_end() const { return current >= source.length(); }
  bool is_digit(const wchar_t digit) const;

  void comment();
  void string();
  void identifier(const wchar_t first_char);
  void number(const wchar_t first_digit);

public:
  Scanner(const std::wstring source) : source(source) {};
  std::vector<Mango::Token> scan();
};
} // namespace Mango

#endif // INCLUDE_SRC_SCANNER_HPP_
