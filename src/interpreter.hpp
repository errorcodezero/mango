#ifndef INCLUDE_SRC_INTERPRETER_HPP_
#define INCLUDE_SRC_INTERPRETER_HPP_

#include "data.hpp"
#include "expression.hpp"
#include "statement.hpp"
#include "visitor.hpp"
#include <cassert>
#include <vector>

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
  virtual VisitResult visit(ExpressionStatement *statement) override;
  virtual VisitResult visit(PrintStatement *statement) override;
  bool is_truthy(Data *data);

public:
  VisitResult evaluate(Expression *expression) {
    assert(expression != nullptr);
    return expression->accept(*this);
  }
  VisitResult evaluate(Statement *statement) {
    assert(statement != nullptr);
    return statement->accept(*this);
  }
  void interpret(std::vector<Statement *> &statements) {
    for (Statement *statement : statements) {
      evaluate(statement);
      delete statement;
    }
  }
};
} // namespace Mango
#endif // INCLUDE_SRC_INTERPRETER_HPP_
