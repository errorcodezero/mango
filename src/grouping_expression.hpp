#ifndef INCLUDE_SRC_GROUPING_HPP_
#define INCLUDE_SRC_GROUPING_HPP_

#include "expression.hpp"
#include "visitor.hpp"
#include <cassert>

namespace Mango {
class GroupingExpression : public Mango::Expression {
  Expression *expression;

public:
  GroupingExpression(Expression *expression) {
    assert(expression != nullptr);

    this->expression = expression;
  }

  ~GroupingExpression() { delete expression; }

  GroupingExpression(GroupingExpression &expr) { expression = expr.expression; }

  GroupingExpression &operator=(const GroupingExpression &expr) {
    if (this != &expr) {
      expression = expr.expression;
    }
    return *this;
  }
  virtual VisitResult accept(Visitor &visitor) { return visitor.visit(this); }

  Expression *getExpression() { return expression; }
};
} // namespace Mango
#endif // INCLUDE_SRC_GROUPING_HPP_
