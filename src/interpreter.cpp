#include "interpreter.hpp"
#include "binary_expression.hpp"
#include "data.hpp"
#include "grouping_expression.hpp"
#include "literal_expression.hpp"
#include "token.hpp"
#include "unary_expression.hpp"
#include "visitor.hpp"
#include <cassert>
#include <cmath>
#include <cstdint>
#include <variant>

namespace Mango {
VisitResult Interpreter::visit(LiteralExpression *expression) {
  assert(expression != nullptr);
  return VisitResult(expression->get_data());
}

VisitResult Interpreter::visit(GroupingExpression *expression) {
  assert(expression != nullptr);
  return evaluate(expression->get_expression());
}

VisitResult Interpreter::visit(UnaryExpression *expression) {
  VisitResult right = evaluate(expression->get_right());

  switch (expression->get_operator()->type) {
  case TokenType::MINUS: {
    Data *right_data = std::get<Data *>(right);

    try {
      std::int32_t number = std::get<std::int32_t>(*right_data);
      return VisitResult(new Data(number * -1));
    } catch (std::bad_variant_access &error) {
      std::double_t number = std::get<std::double_t>(*right_data);
      return VisitResult(new Data(number * -1.0));
    }
  }
  case TokenType::BANG: {
    Data *right_data = std::get<Data *>(right);
    return VisitResult(new Data(!is_truthy(right_data)));
  }
  default: {
    throw;
  }
  }
}

VisitResult Interpreter::visit(BinaryExpression *expression) {
  VisitResult left = evaluate(expression->get_left());
  VisitResult right = evaluate(expression->get_right());

  switch (expression->get_operator()->type) {
  // TODO: Add string concat for plus
  case TokenType::PLUS: {
    bool integer = true;
    Data *left_data = std::get<Data *>(left);
    Data *right_data = std::get<Data *>(right);
    std::double_t sum = 0.0;

    try {
      std::int32_t number = std::get<std::int32_t>(*left_data);
      sum += number;
    } catch (std::bad_variant_access &error) {
      std::double_t number = std::get<std::double_t>(*left_data);
      sum += number;
      integer = false;
    }

    try {
      std::int32_t number = std::get<std::int32_t>(*right_data);
      sum += number;
    } catch (std::bad_variant_access &error) {
      std::double_t number = std::get<std::double_t>(*right_data);
      sum += number;
      integer = false;
    }

    if (integer) {
      return VisitResult(new Data(static_cast<std::int32_t>(sum)));
    }
    return VisitResult(new Data(sum));
  }
  case TokenType::MINUS: {
    bool integer = true;
    Data *left_data = std::get<Data *>(left);
    Data *right_data = std::get<Data *>(right);
    std::double_t diff = 0.0;

    try {
      std::int32_t number = std::get<std::int32_t>(*left_data);
      diff += number;
    } catch (std::bad_variant_access &error) {
      std::double_t number = std::get<std::double_t>(*left_data);
      diff += number;
      integer = false;
    }

    try {
      std::int32_t number = std::get<std::int32_t>(*right_data);
      diff -= number;
    } catch (std::bad_variant_access &error) {
      std::double_t number = std::get<std::double_t>(*right_data);
      diff -= number;
      integer = false;
    }

    if (integer) {
      return VisitResult(new Data(static_cast<std::int32_t>(diff)));
    }
    return VisitResult(new Data(diff));
  }
  case TokenType::STAR: {
    bool integer = true;
    Data *left_data = std::get<Data *>(left);
    Data *right_data = std::get<Data *>(right);
    std::double_t prod = 0.0;

    try {
      std::int32_t number = std::get<std::int32_t>(*left_data);
      prod += number;
    } catch (std::bad_variant_access &error) {
      std::double_t number = std::get<std::double_t>(*left_data);
      prod += number;
      integer = false;
    }

    try {
      std::int32_t number = std::get<std::int32_t>(*right_data);
      prod *= number;
    } catch (std::bad_variant_access &error) {
      std::double_t number = std::get<std::double_t>(*right_data);
      prod *= number;
      integer = false;
    }

    if (integer) {
      return VisitResult(new Data(static_cast<std::int32_t>(prod)));
    }
    return VisitResult(new Data(prod));
  }
  case TokenType::SLASH: {
    bool integer = true;
    Data *left_data = std::get<Data *>(left);
    Data *right_data = std::get<Data *>(right);
    std::double_t quot = 0.0;

    try {
      std::int32_t number = std::get<std::int32_t>(*left_data);
      quot += number;
    } catch (std::bad_variant_access &error) {
      std::double_t number = std::get<std::double_t>(*left_data);
      quot += number;
      integer = false;
    }

    try {
      std::int32_t number = std::get<std::int32_t>(*right_data);
      quot /= number;
    } catch (std::bad_variant_access &error) {
      std::double_t number = std::get<std::double_t>(*right_data);
      quot /= number;
      integer = false;
    }

    if (integer) {
      return VisitResult(new Data(static_cast<std::int32_t>(quot)));
    }
    return VisitResult(new Data(quot));
  }
  default: {
    throw;
  }
  }
}

bool Interpreter::is_truthy(Data *data) {
  if (auto *v = std::get_if<bool>(data)) {
    return *v;
  } else if (auto *v = std::get_if<std::int32_t>(data)) {
    return *v != 0;
  } else if (auto *v = std::get_if<std::double_t>(data)) {
    return *v != 0;
  }

  return true;
}
} // namespace Mango
