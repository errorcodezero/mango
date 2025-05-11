#include "ast_printer.hpp"
#include "binary_expression.hpp"
#include "expression.hpp"
#include "grouping_expression.hpp"
#include "literal_expression.hpp"
#include "unary_expression.hpp"
#include "visitor.hpp"
#include <iostream>
#include <string>
#include <variant>

namespace Mango {
std::wstring AstPrinter::parenthesize(std::wstring name,
                                      Expression *expression1,
                                      Expression *expression2) {
  std::wstring builder = L"( ";
  if (expression1 != nullptr) {
    builder += std::get<std::wstring>(expression1->accept(*this));
    builder += L" ";
  }
  builder += name;
  builder += L" ";
  if (expression2 != nullptr) {
    builder += std::get<std::wstring>(expression2->accept(*this));
    builder += L" ";
  }
  builder += L")";
  return builder;
}
VisitResult AstPrinter::visit(GroupingExpression *expression) {
  return parenthesize(L"group", expression->get_expression(), nullptr);
}
VisitResult AstPrinter::visit(LiteralExpression *expression) {
  Data *data = expression->get_data();
  if (auto *v = std::get_if<std::int32_t>(data)) {
    return std::to_wstring(*v);
  } else if (auto *v = std::get_if<std::double_t>(data)) {
    return std::to_wstring(*v);
  } else if (auto *v = std::get_if<bool>(data)) {
    return v ? L"true" : L"false";
  } else {
    return std::get<std::wstring>(*data);
  }
}
VisitResult AstPrinter::visit(UnaryExpression *expression) {
  return parenthesize(expression->get_operator()->to_string(),
                      expression->get_right(), nullptr);
}
VisitResult AstPrinter::visit(BinaryExpression *expression) {
  return parenthesize(expression->get_operator()->to_string(),
                      expression->get_left(), expression->get_right());
}
VisitResult AstPrinter::visit(ExpressionStatement *statement) {
  std::cout << &statement;
  return std::monostate();
}
VisitResult AstPrinter::visit(PrintStatement *statement) {
  std::cout << &statement;
  return std::monostate();
}
} // namespace Mango
