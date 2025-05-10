#ifndef INCLUDE_SRC_EXPRESSION_HPP_
#define INCLUDE_SRC_EXPRESSION_HPP_

#include "visitor.hpp"

class Visitor;

namespace Mango {
class Expression {
public:
  virtual ~Expression() {};
  virtual VisitResult accept(Visitor &visitor) = 0;
  void interpret();
  void print();
};
} // namespace Mango

#endif // INCLUDE_SRC_EXPRESSION_HPP_
