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
#include <sstream>
#include <string>
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
      delete right_data;
      return VisitResult(new Data(number * -1));
    } catch (std::bad_variant_access &error) {
      std::double_t number = std::get<std::double_t>(*right_data);
      delete right_data;
      return VisitResult(new Data(number * -1.0));
    }
  }
  case TokenType::BANG: {
    Data *right_data = std::get<Data *>(right);
    Data *result = new Data(!is_truthy(right_data));
    delete right_data;
    return result;
  }
  default: {
    throw;
  }
  }
}

VisitResult Interpreter::visit(BinaryExpression *expression) {
  VisitResult left = evaluate(expression->get_left());
  VisitResult right = evaluate(expression->get_right());

  Data *left_data = std::get<Data *>(left);
  Data *right_data = std::get<Data *>(right);

  switch (expression->get_operator()->type) {
  case TokenType::PLUS: {
    bool integer = true;
    bool string = false;
    std::double_t sum = 0.0;
    std::wstringstream buffer = std::wstringstream(L"");

    if (auto *v = std::get_if<std::int32_t>(left_data)) {
      sum += *v;
    } else if (auto *v = std::get_if<std::double_t>(left_data)) {
      sum += *v;
      integer = false;
    } else if (auto *v = std::get_if<std::wstring>(left_data)) {
      string = true;
      if (auto *w = std::get_if<std::int32_t>(right_data)) {
        v->append(std::to_wstring(*w));
      } else if (auto *w = std::get_if<std::double_t>(right_data)) {
        v->append(std::to_wstring(*w));
      } else if (auto *w = std::get_if<std::wstring>(right_data)) {
        v->append(*w);
        string = true;
        buffer << *v;
      } else {
        throw;
      }
    } else {
      throw;
    }

    if (!string) {
      if (auto *v = std::get_if<std::int32_t>(right_data)) {
        sum += *v;
      } else if (auto *v = std::get_if<std::double_t>(right_data)) {
        sum += *v;
        integer = false;
      } else if (auto *v = std::get_if<std::wstring>(right_data)) {
        string = true;
        if (auto *w = std::get_if<std::int32_t>(left_data)) {
          v->append(std::to_wstring(*w));
        } else if (auto *w = std::get_if<std::double_t>(left_data)) {
          v->append(std::to_wstring(*w));
        } else if (auto *w = std::get_if<std::wstring>(left_data)) {
          v->append(*w);
          buffer << *v;
        } else {
          throw;
        }
      } else {
        throw;
      }
    }

    delete left_data;
    delete right_data;
    if (string) {
      return VisitResult(new Data(buffer.str()));
    }
    if (integer) {
      return VisitResult(new Data(static_cast<std::int32_t>(sum)));
    }
    return VisitResult(new Data(sum));
  }
  case TokenType::MINUS: {
    bool integer = true;
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

    delete left_data;
    delete right_data;

    if (integer) {
      return VisitResult(new Data(static_cast<std::int32_t>(diff)));
    }
    return VisitResult(new Data(diff));
  }
  case TokenType::STAR: {
    bool integer = true;
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

    delete left_data;
    delete right_data;

    if (integer) {
      return VisitResult(new Data(static_cast<std::int32_t>(prod)));
    }
    return VisitResult(new Data(prod));
  }
  case TokenType::SLASH: {
    bool integer = true;
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

    delete left_data;
    delete right_data;

    if (integer) {
      return VisitResult(new Data(static_cast<std::int32_t>(quot)));
    }
    return VisitResult(new Data(quot));
  }
  case TokenType::BANG_EQUAL: {
    return VisitResult(new Data(*left_data != *right_data));
  }
  case TokenType::EQUAL_EQUAL: {
    return VisitResult(new Data(*left_data == *right_data));
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
