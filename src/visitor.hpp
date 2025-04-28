#ifndef INCLUDE_SRC_VISITOR_HPP_
#define INCLUDE_SRC_VISITOR_HPP_

#include <string>
#include <variant>
namespace Mango {

using VisitResult = std::variant<std::wstring>;

class GroupingExpression;
class LiteralExpression;
class UnaryExpression;
class BinaryExpression;

class Visitor {
public:
  virtual VisitResult visit(GroupingExpression *expression) = 0;
  virtual VisitResult visit(LiteralExpression *expression) = 0;
  virtual VisitResult visit(UnaryExpression *expression) = 0;
  virtual VisitResult visit(BinaryExpression *expression) = 0;
};
} // namespace Mango
#endif // INCLUDE_SRC_VISITOR_HPP_
