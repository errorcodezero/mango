#ifndef INCLUDE_SRC_AST_PRINTER_HPP_
#define INCLUDE_SRC_AST_PRINTER_HPP_

#include "expression.hpp"
#include "visitor.hpp"
#include <cassert>
#include <string>

namespace Mango {
class AstPrinter : public Visitor {
  virtual VisitResult visit(GroupingExpression *expression);
  virtual VisitResult visit(LiteralExpression *expression);
  virtual VisitResult visit(UnaryExpression *expression);
  virtual VisitResult visit(BinaryExpression *expression);
  std::wstring parenthesize(std::wstring name, Expression *expression1,
                            Expression *expression2);

public:
  std::wstring print(Expression &expression) {
    return std::get<std::wstring>(expression.accept(*this));
  }
};
} // namespace Mango

#endif // INCLUDE_SRC_AST_PRINTER_HPP_
