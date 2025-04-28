#ifndef INCLUDE_SRC_UNARY_EXPRESSION_HPP_
#define INCLUDE_SRC_UNARY_EXPRESSION_HPP_

#include "expression.hpp"
#include "token.hpp"
#include "visitor.hpp"
#include <cassert>

namespace Mango {
class UnaryExpression : Mango::Expression {
  Expression *right;
  Token oper;

  UnaryExpression(Expression *right, Token oper) {
    assert(right != nullptr);

    this->right = right;
    this->oper = oper;
  }

  ~UnaryExpression() { delete right; }

  UnaryExpression(UnaryExpression &expr) {
    expr.oper = oper;
    expr.right = right;
  }

  UnaryExpression &operator=(const UnaryExpression &expr) {
    if (this != &expr) {
      right = expr.right;
      oper = expr.oper;
    }
    return *this;
  }

  virtual VisitResult accept(Visitor &visitor) { return visitor.visit(this); }

public:
  Expression *getRight() { return right; }
};
} // namespace Mango
#endif // INCLUDE_SRC_UNARY_EXPRESSION_HPP_
