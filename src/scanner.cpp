#include "scanner.hpp"
#include "mango.hpp"
#include "token.hpp"
#include <cassert>
#include <cstdint>
#include <optional>
#include <string>
#include <utility>

std::vector<Mango::Token> Mango::Scanner::scan() {
  using namespace std::string_literals;
  while (!at_end()) {
    const std::optional<wchar_t> c = advance();

    assert(c.has_value());

    switch (*c) {
    case '(':
      push_token(TokenType::LEFT_PAREN);
      break;
    case ')':
      push_token(TokenType::RIGHT_PAREN);
      break;
    case '{':
      push_token(TokenType::LEFT_BRACE);
      break;
    case '}':
      push_token(TokenType::RIGHT_BRACE);
      break;
    case ',':
      push_token(TokenType::COMMA);
      break;
    case '.':
      push_token(TokenType::DOT);
      break;
    case '-':
      push_token(TokenType::MINUS);
      break;
    case '+':
      push_token(TokenType::PLUS);
      break;
    case ';':
      push_token(TokenType::SEMICOLON);
      break;
    case '*':
      push_token(TokenType::STAR);
      break;
    case '/':
      push_token(TokenType::SLASH);
      break;
    case '=':
      match_push_token('=', TokenType::EQUAL, TokenType::EQUAL_EQUAL);
      break;
    case '!':
      match_push_token('=', TokenType::BANG_EQUAL, TokenType::BANG);
      break;
    case '<':
      match_push_token('=', TokenType::LESS_EQUAL, TokenType::LESS);
      break;
    case '>':
      match_push_token('=', TokenType::GREATER_EQUAL, TokenType::GREATER);
      break;
    case '#':
      comment();
      break;
    case ' ':
    case '\r':
    case '\t':
      break;
    case '\n':
      line++;
      break;
    case '0':
    case '1':
    case '2':
    case '3':
    case '4':
    case '5':
    case '6':
    case '7':
    case '8':
    case '9':
      break;
    case '"':
      string();
      break;
    default:
      Mango::error(&"Unexpected character: "[*c], "program", line);
      break;
    }
  }
  return std::move(tokens);
}

std::optional<wchar_t> Mango::Scanner::advance() {
  if (!at_end()) {
    const wchar_t c = source.at(++current);
    return std::make_optional(c);
  } else {
    return std::nullopt;
  }
}

std::optional<wchar_t> Mango::Scanner::peek() {
  if (!at_end()) {
    const wchar_t c = source.at(current + 1);
    return std::make_optional(c);
  } else {
    return std::nullopt;
  }
}

void Mango::Scanner::push_token(const Mango::TokenType type) {
  tokens.push_back(Token{.type = type, .lexeme = std::nullopt});
};

void Mango::Scanner::push_token(const Mango::TokenType type,
                                const Mango::Lexeme lexeme) {
  tokens.push_back(Token{.type = type, .lexeme = std::make_optional(lexeme)});
}

bool Mango::Scanner::match(wchar_t expected) {
  if (at_end())
    return false;

  if (source.at(current) != expected)
    return false;

  current++;
  return true;
}

void Mango::Scanner::match_push_token(wchar_t expected, const TokenType type,
                                      const TokenType fallback_type) {
  push_token(match(expected) ? type : fallback_type);
}

void Mango::Scanner::comment() {
  while (!at_end()) {
    std::optional<wchar_t> peeked = peek();
    assert(peeked.has_value());

    if (*peeked == '\n')
      break;

    advance();
  }
}

void Mango::Scanner::string() {
  uint32_t start = current;
  uint32_t num = 0;

  while (!at_end()) {
    std::optional<wchar_t> peeked = peek();
    assert(peeked.has_value());
    if (*peeked == '"') {
      advance();
      break;
    }
    num++;
  }
  push_token(TokenType::STRING_LITERAL,
             Lexeme{.line = current, .data = {source.substr(start, num)}});
}

void Mango::Scanner::number(const wchar_t first_digit) {
  assert(Scanner::is_digit(first_digit));

  std::string number = "";
  number += first_digit;
  bool floating_point = false;

  while (!at_end()) {
    assert(peek().has_value());

    if (!is_digit(*peek()) && *peek() != '.') {
      if (*peek() == '.') {
        floating_point = true;
      }
      number += *peek();
      advance();
    } else {
      break;
    }
  }

  if (floating_point) {
    push_token(TokenType::FLOAT_LITERAL,
               Lexeme{.line = line, .data = {.floatData = std::stod(number)}});
    return;
  }
  push_token(
      TokenType::INT_LITERAL,
      Lexeme{.line = line,
             .data = {.intData = static_cast<uint32_t>(std::stoul(number))}});
}

bool Mango::Scanner::is_digit(const wchar_t first_digit) {
  switch (first_digit) {
  case '0':
  case '1':
  case '2':
  case '3':
  case '4':
  case '5':
  case '6':
  case '7':
  case '8':
  case '9':
    return true;

  default:
    return false;
  }
};
