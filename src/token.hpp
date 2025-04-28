#ifndef INCLUDE_SRC_TOKEN_HPP_
#define INCLUDE_SRC_TOKEN_HPP_

#include "data.hpp"
#include <cmath>
#include <cstdint>

namespace Mango {

struct Lexeme {
  uint32_t line;
  Data *data;
};

enum class TokenType {
  // Single-character tokens.
  LEFT_PAREN,
  RIGHT_PAREN,
  LEFT_BRACE,
  RIGHT_BRACE,
  COMMA,
  DOT,
  MINUS,
  PLUS,
  SEMICOLON,
  SLASH,
  STAR,

  // One or two character tokens.
  BANG,
  BANG_EQUAL,
  EQUAL,
  EQUAL_EQUAL,
  PLUS_EQUAL,
  MINUS_EQUAL,
  STAR_EQUAL,
  SLASH_EQUAL,
  GREATER,
  GREATER_EQUAL,
  LESS,
  LESS_EQUAL,
  AMPERSAND,
  AMPERSAND_AMPERSAND,
  BAR,
  BAR_BAR,
  HASHTAG,

  // Literals.
  IDENTIFIER,
  STRING_LITERAL,
  INT_LITERAL,
  FLOAT_LITERAL,
  BOOL_LITERAL,

  // Keywords.
  CLASS,
  ELSE,
  FALSE,
  SUB,
  FOR,
  IF,
  NIL,
  PRINT,
  RETURN,
  SUPER,
  THIS,
  TRUE,
  VAR,
  WHILE,
  STRING,
  INT,
  FLOAT,
  BOOL,

  // End of file
  END_OF_FILE
};
struct Token {
  TokenType type;
  Lexeme lexeme;
};
} // namespace Mango

#endif // INCLUDE_SRC_TOKEN_HPP_
