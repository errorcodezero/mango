#ifndef INCLUDE_SRC_EXPRESSION_STATEMENT_HPP_
#define INCLUDE_SRC_EXPRESSION_STATEMENT_HPP_

#include "expression.hpp"
#include "statement.hpp"

namespace Mango {
class ExpressionStatement : public Statement {
private:
  Expression *expression;

public:
  virtual VisitResult accept(Visitor &visitor) override {
    return visitor.visit(this);
  };
  ExpressionStatement(Expression *expression) : expression(expression) {};
  ExpressionStatement &operator=(const ExpressionStatement &statement) {
    if (this != &statement) {
      expression = statement.expression;
    }
    return *this;
  }
  ExpressionStatement(ExpressionStatement &statement) {
    expression = statement.expression;
  }
  virtual ~ExpressionStatement() { delete expression; }
  Expression *get_expression() { return expression; }
};
} // namespace Mango
#endif // INCLUDE_SRC_EXPRESSION_STATEMENT_HPP_
