#include "parser.hpp"
#include "expression.hpp"
#include "token.hpp"
#include <cassert>
#include <optional>

Mango::Expression *Mango::Parser::expression() { return equality(); }

Mango::Expression *Mango::Parser::equality() {
  Expression *expression = comparison();

  while (match({TokenType::BANG_EQUAL, TokenType::EQUAL_EQUAL})) {
  }

  return expression;
}

bool Mango::Parser::match(std::initializer_list<Mango::TokenType> types) {
  for (TokenType type : types) {
    if (check(type)) {
      advance();
      return true;
    }
  }

  return false;
}

bool Mango::Parser::check(TokenType type) {
  if (at_end())
    return false;
  assert(peek().has_value());
  return peek()->get().type == type;
}

std::optional<std::reference_wrapper<Mango::Token>> Mango::Parser::peek() {
  if (!at_end())
    return std::make_optional(
        std::reference_wrapper<Token>(tokens.at(current)));
  else
    return std::nullopt;
}

std::optional<std::reference_wrapper<Mango::Token>>
Mango::Parser::peekPrevious() {
  if (!at_start())
    return std::make_optional(
        std::reference_wrapper<Token>(tokens.at(current - 1)));
  else
    return std::nullopt;
}

Mango::Expression *Mango::Parser::comparison() {
  Expression *expression = term();

  while (match({TokenType::GREATER, TokenType::GREATER_EQUAL,
                TokenType::LESS_EQUAL, TokenType::LESS})) {
    // TODO: Implement this
  }

  return expression;
}

Mango::Expression *Mango::Parser::term() {
  Expression *expression = nullptr;
  return expression;
}
