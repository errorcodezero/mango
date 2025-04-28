#include "parser.hpp"
#include "binary_expression.hpp"
#include "data.hpp"
#include "expression.hpp"
#include "grouping_expression.hpp"
#include "literal_expression.hpp"
#include "token.hpp"
#include "unary_expression.hpp"
#include "visitor.hpp"
#include <cassert>
#include <optional>

Mango::Expression *Mango::Parser::expression() { return equality(); }

Mango::Expression *Mango::Parser::equality() {
  Expression *expression = comparison();
  assert(expression != nullptr);

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
  return peek().type == type;
}

std::optional<std::reference_wrapper<Mango::Token>>
Mango::Parser::peek_previous() {
  if (!at_start())
    return std::make_optional(
        std::reference_wrapper<Token>(tokens.at(current - 1)));
  else
    return std::nullopt;
}

Mango::Expression *Mango::Parser::comparison() {
  Expression *expression = term();
  assert(expression != nullptr);

  while (match({TokenType::GREATER, TokenType::GREATER_EQUAL,
                TokenType::LESS_EQUAL, TokenType::LESS})) {
    std::optional<std::reference_wrapper<Token>> oper = peek_previous();
    assert(oper.has_value());
    Expression *right = term();
    expression = new BinaryExpression(expression, right, oper->get());
  }

  return expression;
}

Mango::Expression *Mango::Parser::term() {
  Expression *expression = factor();
  assert(expression != nullptr);

  while (match({TokenType::MINUS, TokenType::PLUS})) {
    std::optional<std::reference_wrapper<Token>> oper = peek_previous();
    assert(oper.has_value());
    Expression *right = factor();
    expression = new BinaryExpression(expression, right, *oper);
  }
  return expression;
}

Mango::Expression *Mango::Parser::factor() {
  Expression *expression = unary();
  assert(expression != nullptr);

  while (match({TokenType::SLASH, TokenType::STAR})) {
    std::optional<std::reference_wrapper<Token>> oper = peek_previous();
    Expression *right = unary();
    expression = new BinaryExpression(expression, right, *oper);
  }

  return expression;
}

Mango::Expression *Mango::Parser::unary() {
  if (match({TokenType::BANG, TokenType::MINUS})) {
    std::optional<std::reference_wrapper<Token>> oper = peek_previous();
    Expression *right = unary();
    assert(right != nullptr);
    Expression *expression = new UnaryExpression(right, *oper);
    assert(expression != nullptr);

    return expression;
  }

  return primary();
}

Mango::Expression *Mango::Parser::primary() {
  Expression *expression = nullptr;
  if (match({TokenType::FALSE})) {
    expression = new LiteralExpression(new Data(false));
    goto end;
  } else if (match({TokenType::TRUE})) {
    expression = new LiteralExpression(new Data(true));
    goto end;
  } else if (match({TokenType::NIL})) {
    expression = new LiteralExpression(nullptr);
    goto end;
  } else if (match({TokenType::INT_LITERAL, TokenType::STRING_LITERAL,
                    TokenType::FLOAT_LITERAL})) {
    assert(peek_previous().has_value());
    expression = new LiteralExpression(peek_previous()->get().lexeme.data);
    goto end;
  } else if (match({TokenType::LEFT_PAREN})) {
    expression = new GroupingExpression(this->expression());
    consume(TokenType::RIGHT_PAREN, L"Expect ')' after expression.");
    goto end;
  }

  throw;

end:
  assert(expression != nullptr);
  return expression;
}
