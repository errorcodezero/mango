#include "ast_printer.hpp"
#include "binary_expression.hpp"
#include "expression.hpp"
#include "grouping_expression.hpp"
#include "literal_expression.hpp"
#include "unary_expression.hpp"
#include "visitor.hpp"
#include <cstdarg>

namespace Mango {
std::wstring AstPrinter::parenthesize(std::wstring name,
                                      Expression *expression1,
                                      Expression *expression2) {
  std::wstring builder = L"(";
  if (expression1 != nullptr) {
    builder += std::get<std::wstring>(expression1->accept(*this));
    builder += L" ";
  }
  if (expression2 != nullptr) {
    builder += std::get<std::wstring>(expression2->accept(*this));
    builder += L" ";
  }
  builder += name;
  builder += L")";
  return builder;
}
VisitResult AstPrinter::visit(GroupingExpression *expression) {
  return parenthesize(L"group", expression->get_expression(), nullptr);
}
VisitResult AstPrinter::visit(LiteralExpression *expression) {
  expression->getData();
  return parenthesize(L"LITERAL", nullptr, nullptr);
}
VisitResult AstPrinter::visit(UnaryExpression *expression) {
  return parenthesize(L"OPERATION", expression->get_right(), nullptr);
}
VisitResult AstPrinter::visit(BinaryExpression *expression) {
  return parenthesize(L"OPERATION", expression->get_left(),
                      expression->get_right());
}
} // namespace Mango
