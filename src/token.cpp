#include "token.hpp"
#include <cmath>
#include <cstdint>

namespace Mango {
std::wstring Token::to_string() {
  switch (this->type) {
  case TokenType::STRING: {
    return L"string";
  }
  case TokenType::PRINT: {
    return L"print";
  }
  case TokenType::BANG: {
    return L"!";
  }
  case TokenType::FOR: {
    return L"for";
  }
  case TokenType::FLOAT: {
    return L"float";
  }
  case TokenType::INT: {
    return L"int";
  }
  case TokenType::RETURN: {
    return L"return";
  }
  case TokenType::CLASS: {
    return L"class";
  }
  case TokenType::AMPERSAND: {
    return L"&";
  }
  case TokenType::AMPERSAND_AMPERSAND: {
    return L"&&";
  }
  case TokenType::BAR: {
    return L"|";
  }
  case TokenType::BAR_BAR: {
    return L"||";
  }
  case TokenType::EQUAL: {
    return L"=";
  }
  case TokenType::EQUAL_EQUAL: {
    return L"==";
  }
  case TokenType::GREATER: {
    return L">";
  }
  case TokenType::GREATER_EQUAL: {
    return L">=";
  }
  case TokenType::LESS: {
    return L"<";
  }
  case TokenType::LESS_EQUAL: {
    return L"<=";
  }
  case TokenType::PLUS: {
    return L"+";
  }
  case TokenType::PLUS_EQUAL: {
    return L"+=";
  }
  case TokenType::MINUS: {
    return L"-";
  }
  case TokenType::MINUS_EQUAL: {
    return L"-=";
  }
  case TokenType::STAR: {
    return L"*";
  }
  case TokenType::STAR_EQUAL: {
    return L"*=";
  }
  case TokenType::SLASH: {
    return L"/";
  }
  case TokenType::SLASH_EQUAL: {
    return L"/=";
  }
  case TokenType::BOOL: {
    return L"bool";
  }
  case TokenType::VAR: {
    return L"var";
  }
  case TokenType::SUPER: {
    return L"super";
  }
  case TokenType::COMMA: {
    return L",";
  }
  case TokenType::DOT: {
    return L".";
  }
  case TokenType::IF: {
    return L"if";
  }
  case TokenType::ELSE: {
    return L"else";
  }
  case TokenType::NIL: {
    return L"nil";
  }
  case TokenType::SEMICOLON: {
    return L";";
  }
  case TokenType::LEFT_BRACE: {
    return L"{";
  }
  case TokenType::RIGHT_BRACE: {
    return L"}";
  }
  case TokenType::LEFT_PAREN: {
    return L"(";
  }
  case TokenType::RIGHT_PAREN: {
    return L")";
  }
  case TokenType::END_OF_FILE: {
    return L"EOF";
  }
  case TokenType::HASHTAG: {
    return L"#";
  }
  case TokenType::WHILE: {
    return L"while";
  }
  case TokenType::IDENTIFIER: {
    return L"identifier";
  }
  case TokenType::BANG_EQUAL: {
    return L"!=";
  }
  case TokenType::THIS: {
    return L"this";
  }
  case TokenType::SUB: {
    return L"sub";
  }
  case TokenType::FALSE: {
    return L"false";
  }
  case TokenType::TRUE: {
    return L"true";
  }
  case TokenType::FLOAT_LITERAL: {
    return std::to_wstring(std::get<std::double_t>(*this->lexeme.data));
  }
  case TokenType::INT_LITERAL: {
    return std::to_wstring(std::get<std::int32_t>(*this->lexeme.data));
  }
  case TokenType::STRING_LITERAL: {
    return std::get<std::wstring>(*this->lexeme.data);
  }
  default: {
    return L"DEFAULT";
  }
  }
}
} // namespace Mango
