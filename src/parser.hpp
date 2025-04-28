#ifndef INCLUDE_SRC_PARSER_HPP_
#define INCLUDE_SRC_PARSER_HPP_

#include "expression.hpp"
#include "token.hpp"
#include <cstdint>
#include <functional>
#include <initializer_list>
#include <optional>
#include <vector>

namespace Mango {
class Parser {
private:
  std::vector<Mango::Token> tokens = std::vector<Mango::Token>();
  uint32_t current = 0;

  Expression *expression();
  Expression *equality();
  Expression *comparison();
  Expression *term();

  bool match(std::initializer_list<TokenType> types);
  bool check(TokenType type);
  bool at_end() { return current >= tokens.size(); }
  bool at_start() { return current <= tokens.size(); }
  std::optional<std::reference_wrapper<Token>> advance();
  std::optional<std::reference_wrapper<Token>> peek();
  std::optional<std::reference_wrapper<Token>> peekPrevious();

public:
  Parser(std::vector<Mango::Token> tokens) : tokens(tokens) {};
};
} // namespace Mango
#endif // INCLUDE_SRC_PARSER_HPP_
