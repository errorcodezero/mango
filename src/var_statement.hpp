#ifndef INCLUDE_SRC_VAR_STATEMENT_HPP_
#define INCLUDE_SRC_VAR_STATEMENT_HPP_

#include "expression.hpp"
#include "statement.hpp"
#include "token.hpp"
#include "visitor.hpp"

namespace Mango {

class VarStatement : public Statement {
private:
  Token name;
  Expression *initializer;

public:
  VarStatement(Token name, Expression *initializer)
      : name(name), initializer(initializer) {};
  virtual ~VarStatement() override { delete initializer; }
  VarStatement &operator=(const VarStatement &statement) {
    if (this != &statement) {
      name = statement.name;
      initializer = statement.initializer;
    }
    return *this;
  }
  VarStatement(VarStatement &expr) {
    name = expr.name;
    initializer = expr.initializer;
  }
  VarStatement() {};
  virtual VisitResult accept(Visitor &visitor) override {
    return visitor.visit(this);
  }
};
} // namespace Mango
#endif // INCLUDE_SRC_VAR_STATEMENT_HPP_
