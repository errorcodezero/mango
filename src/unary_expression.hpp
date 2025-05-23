#ifndef INCLUDE_SRC_UNARY_EXPRESSION_HPP_
#define INCLUDE_SRC_UNARY_EXPRESSION_HPP_

#include "expression.hpp"
#include "token.hpp"
#include "visitor.hpp"
#include <cassert>

namespace Mango {
class UnaryExpression : public Mango::Expression {
  Expression *right;
  Token oper;

public:
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

  Expression *get_right() { return right; }
  Token *get_operator() { return &oper; }
};
} // namespace Mango
#endif // INCLUDE_SRC_UNARY_EXPRESSION_HPP_
