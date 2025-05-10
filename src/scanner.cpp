#include "scanner.hpp"
#include "error.hpp"
#include "token.hpp"
#include <cassert>
#include <cstdint>
#include <optional>
#include <sstream>
#include <string>
#include <utility>

namespace Mango {
std::vector<Token> Scanner::scan() {
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
      match_push_token('=', TokenType::EQUAL_EQUAL, TokenType::EQUAL);
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
    case '&':
      match_push_token('&', TokenType::AMPERSAND_AMPERSAND,
                       TokenType::AMPERSAND);
      break;
    case '|':
      match_push_token('|', TokenType::BAR_BAR, TokenType::BAR);
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
      number(*c);
      break;
    case '"':
      string();
      break;
    default:
      if (is_alpha(*c)) {
        identifier(*c);
      } else {
        std::wstring error = L"Unexpected character: ";
        error += *c;
        Mango::error(error, L"program", line);
        break;
      }
    }
  }
  return std::move(tokens);
}

std::optional<wchar_t> Scanner::advance() {
  if (!at_end()) {
    const wchar_t c = source.at(current++);
    return std::make_optional(c);
  } else {
    return std::nullopt;
  }
}

std::optional<wchar_t> Scanner::peek() {
  if (!at_end()) {
    const wchar_t c = source.at(current);
    return std::make_optional(c);
  } else {
    return std::nullopt;
  }
}

void Scanner::push_token(const TokenType type) {
  tokens.push_back(
      Token{.type = type, .lexeme = {.line = line, .data = nullptr}});
};

void Scanner::push_token(const TokenType type, const Lexeme lexeme) {
  tokens.push_back(Token{.type = type, .lexeme = lexeme});
}

bool Scanner::match(const wchar_t expected) {
  if (at_end())
    return false;

  assert(peek().has_value());

  if (*peek() != expected)
    return false;

  advance();
  return true;
}

void Scanner::match_push_token(wchar_t expected, const TokenType type,
                               const TokenType fallback_type) {
  push_token(match(expected) ? type : fallback_type);
}

void Scanner::comment() {
  while (!at_end()) {
    std::optional<wchar_t> peeked = peek();
    assert(peeked.has_value());

    if (*peeked == '\n')
      break;

    advance();
  }
}

void Scanner::string() {
  std::wstringstream str;

  while (!at_end()) {
    std::optional<wchar_t> peeked = peek();
    assert(peeked.has_value());
    if (*peeked == '"') {
      advance();
      break;
    }
    str << *peeked;
    advance();
  }
  push_token(TokenType::STRING_LITERAL,
             Lexeme{.line = line, .data = new Data(str.str())});
}

void Scanner::number(const wchar_t first_digit) {
  std::string number = "";
  number += first_digit;
  bool floating_point = false;

  while (!at_end()) {
    assert(peek().has_value());

    if (is_digit(*peek()) || *peek() == '.') {
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
               Lexeme{.line = line,
                      .data = new Data(
                          static_cast<std::double_t>(std::stod(number)))});
    return;
  }
  push_token(
      TokenType::INT_LITERAL,
      Lexeme{.line = line,
             .data = new Data(static_cast<std::int32_t>(std::stoul(number)))});
}

void Scanner::identifier(const wchar_t first_char) {
  std::wstring identifier = L"";
  identifier += first_char;

  assert(peek().has_value());

  while (!at_end() && is_alphanumeric(*peek())) {
    assert(peek().has_value());

    identifier += *peek();
    advance();
  }

  advance();

  if (identifier == L"true") {
    push_token(TokenType::TRUE);
  } else if (identifier == L"true") {
    push_token(TokenType::TRUE);
  } else if (identifier == L"false") {
    push_token(TokenType::FALSE);
  } else if (identifier == L"class") {
    push_token(TokenType::CLASS);
  } else if (identifier == L"super") {
    push_token(TokenType::SUPER);
  } else if (identifier == L"this") {
    push_token(TokenType::THIS);
  } else {
    push_token(TokenType::IDENTIFIER,
               Lexeme{.line = line, .data = new Data(identifier)});
  }
}
} // namespace Mango
