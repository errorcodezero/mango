#ifndef INCLUDE_SRC_PARSER_HPP_
#define INCLUDE_SRC_PARSER_HPP_

#include "error.hpp"
#include "expression.hpp"
#include "statement.hpp"
#include "token.hpp"
#include <cassert>
#include <cstdint>
#include <functional>
#include <initializer_list>
#include <iostream>
#include <optional>
#include <vector>

namespace Mango {
class Parser {
private:
  std::vector<Token> tokens = std::vector<Token>();
  uint32_t current = 0;

  Expression *expression();
  Expression *equality();
  Expression *comparison();
  Expression *term();
  Expression *factor();
  Expression *unary();
  Expression *primary();

  Statement *statement();
  Statement *print_statement();
  Statement *expression_statement();

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

    // error(type, message);
    message.append(L"");
    throw;
  };

public:
  Parser(std::vector<Token> tokens) : tokens(tokens) {};
  std::vector<Statement *> parse();
};
} // namespace Mango
#endif // INCLUDE_SRC_PARSER_HPP_
