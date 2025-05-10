#include "expression.hpp"
#include "ast_printer.hpp"
#include "interpreter.hpp"
#include <iostream>

namespace Mango {
void Expression::interpret() {
  Interpreter interpreter = Interpreter();

  Mango::Data *data = std::get<Mango::Data *>(interpreter.evaluate(this));

  if (auto *v = std::get_if<std::int32_t>(data)) {
    std::wcout << *v;
  } else if (auto *v = std::get_if<std::double_t>(data)) {
    std::wcout << *v;
  } else if (auto *v = std::get_if<bool>(data)) {
    std::wcout << (*v ? L"true" : L"false");
  } else if (auto *v = std::get_if<std::wstring>(data)) {
    std::wcout << *v;
  }

  std::wcout << "\n";

  delete data;
}

void Expression::print() {
  AstPrinter printer = AstPrinter();
  std::wcout << printer.print(*this) << "\n";
}
} // namespace Mango
