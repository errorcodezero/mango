#include "expression.hpp"
#include "token.hpp"
#include "visitor.hpp"
#include <cassert>

#ifndef INCLUDE_SRC_BINARY_EXPRESSION_HPP_
#define INCLUDE_SRC_BINARY_EXPRESSION_HPP_
namespace Mango {
class BinaryExpression : public Mango::Expression {
  Expression *left;
  Expression *right;
  Token oper;

  BinaryExpression(Expression *left, Expression *right, Token oper) {
    assert(left != nullptr);
    assert(right != nullptr);
    assert(left != right);

    this->left = left;
    this->right = right;
    this->oper = oper;
  }

  ~BinaryExpression() {
    delete left;
    delete right;
  }

  BinaryExpression(BinaryExpression &expr) {
    expr.oper = oper;
    expr.right = right;
    expr.left = left;
  }

  BinaryExpression &operator=(const BinaryExpression &expr) {
    if (this != &expr) {
      left = expr.left;
      right = expr.right;
      oper = expr.oper;
    }
    return *this;
  }

  virtual VisitResult accept(Visitor &visitor) { return visitor.visit(this); }

public:
  Expression *getLeft() { return left; }
  Expression *getRight() { return right; }
};
} // namespace Mango
#endif // INCLUDE_SRC_BINARY_EXPRESSION_HPP_
