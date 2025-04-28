#include "ast_printer.hpp"
#include "binary_expression.hpp"
#include "expression.hpp"
#include "grouping_expression.hpp"
#include "literal_expression.hpp"
#include "unary_expression.hpp"
#include "visitor.hpp"
#include <cstdarg>

std::wstring Mango::AstPrinter::parenthesize(std::wstring name,
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
Mango::VisitResult
Mango::AstPrinter::visit(Mango::GroupingExpression *expression) {
  return parenthesize(L"group", expression->getExpression(), nullptr);
}
Mango::VisitResult
Mango::AstPrinter::visit(Mango::LiteralExpression *expression) {
  expression->getData();
  return parenthesize(L"LITERAL", nullptr, nullptr);
}
Mango::VisitResult
Mango::AstPrinter::visit(Mango::UnaryExpression *expression) {
  return parenthesize(L"OPERATION", expression->getRight(), nullptr);
}
Mango::VisitResult
Mango::AstPrinter::visit(Mango::BinaryExpression *expression) {
  return parenthesize(L"OPERATION", expression->getLeft(),
                      expression->getRight());
}
