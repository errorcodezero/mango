#ifndef INCLUDE_SRC_LITERAL_HPP_
#define INCLUDE_SRC_LITERAL_HPP_

#include "data.hpp"
#include "expression.hpp"
#include "visitor.hpp"
#include <cassert>

namespace Mango {
class LiteralExpression : public Mango::Expression {
  Data *data;

public:
  LiteralExpression(Data *data) { this->data = data; }

  ~LiteralExpression() {}

  LiteralExpression(LiteralExpression &expr) { data = expr.data; }

  LiteralExpression &operator=(const LiteralExpression &expr) {
    if (this != &expr) {
      data = expr.data;
    }
    return *this;
  }

  virtual VisitResult accept(Visitor &visitor) { return visitor.visit(this); }

  Data *getData() { return data; }
};
} // namespace Mango
#endif // INCLUDE_SRC_LITERAL_HPP_
