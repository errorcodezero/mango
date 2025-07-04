#ifndef INCLUDE_SRC_VAR_EXPRESSION_HPP_
#define INCLUDE_SRC_VAR_EXPRESSION_HPP_

#include "expression.hpp"
#include "token.hpp"
namespace Mango {
class VarExpression : public Expression {
private:
  Token name;
};
} // namespace Mango

#endif // INCLUDE_SRC_VAR_EXPRESSION_HPP_
