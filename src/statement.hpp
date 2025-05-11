#ifndef INCLUDE_SRC_STATEMENT_HPP_
#define INCLUDE_SRC_STATEMENT_HPP_

#include "visitor.hpp"

namespace Mango {
class Statement {
public:
  virtual VisitResult accept(Visitor &visitor) = 0;
  virtual ~Statement() {};
};
} // namespace Mango

#endif // INCLUDE_SRC_STATEMENT_HPP_
