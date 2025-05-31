#ifndef INCLUDE_SRC_VISITOR_HPP_
#define INCLUDE_SRC_VISITOR_HPP_

#include "data.hpp"
#include <string>
#include <variant>
namespace Mango {

using VisitResult = std::variant<std::wstring, Data *, std::monostate>;

class GroupingExpression;
class LiteralExpression;
class UnaryExpression;
class BinaryExpression;
class ExpressionStatement;
class PrintStatement;
class VarStatement;

class Visitor {
public:
  virtual VisitResult visit(GroupingExpression *expression) = 0;
  virtual VisitResult visit(LiteralExpression *expression) = 0;
  virtual VisitResult visit(UnaryExpression *expression) = 0;
  virtual VisitResult visit(BinaryExpression *expression) = 0;

  virtual VisitResult visit(ExpressionStatement *statement) = 0;
  virtual VisitResult visit(PrintStatement *statement) = 0;
  virtual VisitResult visit(VarStatement *statement) = 0;
};
} // namespace Mango
#endif // INCLUDE_SRC_VISITOR_HPP_
