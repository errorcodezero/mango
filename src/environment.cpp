#include "environment.hpp"
#include "data.hpp"
#include "parser.hpp"
#include "token.hpp"

namespace Mango {
void Environment::define(std::wstring name, Data *value) {
  values.insert_or_assign(name, value);
}
Data *Environment::get(Token name) {
  if (values.contains(name.to_string())) {
    return values.at(name.to_string());
  }

  error(name.lexeme.line, (L"Undefined variable " + name.to_string()));
  throw;
}
} // namespace Mango
