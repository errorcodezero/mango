#include "parser.hpp"
#include "binary_expression.hpp"
#include "expression.hpp"
#include "expression_statement.hpp"
#include "grouping_expression.hpp"
#include "literal_expression.hpp"
#include "print_statement.hpp"
#include "statement.hpp"
#include "token.hpp"
#include "unary_expression.hpp"
#include "var_expression.hpp"
#include "var_statement.hpp"
#include "visitor.hpp"
#include <cassert>
#include <iterator>
#include <optional>
namespace Mango {
Expression *Parser::expression() { return equality(); }

Statement *Parser::statement() {
  if (match({TokenType::PRINT}))
    return print_statement();

  return expression_statement();
}

Expression *Parser::equality() {
  Expression *expression = comparison();
  assert(expression != nullptr);

  while (match({TokenType::BANG_EQUAL, TokenType::EQUAL_EQUAL})) {
    std::optional<std::reference_wrapper<Token>> oper = peek_previous();
    assert(oper.has_value());
    Expression *right = comparison();
    assert(right != nullptr);
    expression = new BinaryExpression(expression, right, *oper);
  }

  assert(expression != nullptr);
  return expression;
}

bool Parser::match(std::initializer_list<TokenType> types) {
  for (TokenType type : types) {
    if (check(type)) {
      advance();
      return true;
    }
  }

  return false;
}

bool Parser::check(TokenType type) {
  if (at_end())
    return false;
  return peek().type == type;
}

std::optional<std::reference_wrapper<Token>> Parser::peek_previous() {
  if (!at_start())
    return std::make_optional(
        std::reference_wrapper<Token>(tokens.at(current - 1)));
  else
    return std::nullopt;
}

Expression *Parser::comparison() {
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

Expression *Parser::term() {
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

Expression *Parser::factor() {
  Expression *expression = unary();
  assert(expression != nullptr);

  while (match({TokenType::SLASH, TokenType::STAR})) {
    std::optional<std::reference_wrapper<Token>> oper = peek_previous();
    Expression *right = unary();
    expression = new BinaryExpression(expression, right, *oper);
  }

  return expression;
}

Expression *Parser::unary() {
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

Expression *Parser::primary() {
  Expression *expression = nullptr;
  if (match({TokenType::INT_LITERAL, TokenType::STRING_LITERAL,
             TokenType::FLOAT_LITERAL, TokenType::TRUE, TokenType::FALSE})) {
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

Statement *Parser::print_statement() {
  Expression *expression = this->expression();
  consume(TokenType::SEMICOLON, L"Expect ';' after expression.");
  return new PrintStatement(expression);
}
Statement *Parser::expression_statement() {
  Expression *expression = this->expression();
  consume(TokenType::SEMICOLON, L"Expect ';' after expression.");
  return new ExpressionStatement(expression);
}
Statement *Parser::declaration() {
  if (match({TokenType::VAR}))
    return var_declaration();

  return statement();
}
Statement *Parser::var_declaration() {
  Token name = consume(TokenType::IDENTIFIER, L"Expect variable name.");

  Expression *initializer = nullptr;
  if (match({TokenType::EQUAL})) {
    initializer = expression();
  }

  consume(TokenType::SEMICOLON, L"Expect ; after variable declaration.");
  return new VarStatement(name, initializer);
}
std::vector<Statement *> Parser::parse() {
  auto statements = std::vector<Statement *>();
  while (!at_end()) {
    statements.push_back(statement());
  }
  return statements;
}
} // namespace Mango
