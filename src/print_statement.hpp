#include "expression.hpp"
#include "statement.hpp"

namespace Mango {
class PrintStatement : public Statement {
  Expression *expression;

private:
  virtual VisitResult accept(Visitor &visitor) override {
    return visitor.visit(this);
  }

public:
  PrintStatement(Expression *expression) : expression(expression) {}
  virtual ~PrintStatement() { delete expression; }
  Expression *get_expression() { return expression; }
};
} // namespace Mango
