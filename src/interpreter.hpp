#ifndef INCLUDE_SRC_INTERPRETER_HPP_
#define INCLUDE_SRC_INTERPRETER_HPP_

#include "data.hpp"
#include "expression.hpp"
#include "visitor.hpp"
#include <cassert>

namespace Mango {

class LiteralExpression;
class BinaryExpression;
class UnaryExpression;
class GroupingExpression;

class Interpreter : public Visitor {
private:
  virtual VisitResult visit(LiteralExpression *expression) override;
  virtual VisitResult visit(BinaryExpression *expression) override;
  virtual VisitResult visit(UnaryExpression *expression) override;
  virtual VisitResult visit(GroupingExpression *expression) override;
  bool is_truthy(Data *data);

public:
  VisitResult evaluate(Expression *expression) {
    assert(expression != nullptr);
    return expression->accept(*this);
  }
};
} // namespace Mango
#endif // INCLUDE_SRC_INTERPRETER_HPP_
