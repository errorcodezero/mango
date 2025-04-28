#ifndef INCLUDE_SRC_PARSER_HPP_
#define INCLUDE_SRC_PARSER_HPP_

#include "expression.hpp"
#include "mango.hpp"
#include "token.hpp"
#include <cassert>
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
  Expression *factor();
  Expression *unary();
  Expression *primary();

  bool match(std::initializer_list<TokenType> types);
  bool check(TokenType type);
  bool at_end() { return current >= tokens.size(); }
  bool at_start() { return current <= 0; }

  std::optional<std::reference_wrapper<Token>> advance() {
    if (at_end()) {
      return std::nullopt;
    }
    assert(current < tokens.size());
    return std::make_optional(std::reference_wrapper(tokens.at(current++)));
  }
  Token &peek() {
    assert(current <= tokens.size());
    return tokens.at(current);
  }
  std::optional<std::reference_wrapper<Token>> peek_previous();
  std::optional<std::reference_wrapper<Token>> consume(TokenType type,
                                                       std::wstring message) {
    if (check(type)) {
      return advance();
    }

    error(type, message);
    throw;
  };

public:
  Parser(std::vector<Mango::Token> tokens) : tokens(tokens) {};
  Expression *parse() { return expression(); }
};
} // namespace Mango
#endif // INCLUDE_SRC_PARSER_HPP_
