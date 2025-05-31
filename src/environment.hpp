#ifndef INCLUDE_SRC_ENVIRONMENT_HPP_
#define INCLUDE_SRC_ENVIRONMENT_HPP_

#include "data.hpp"
#include "token.hpp"
#include <unordered_map>
namespace Mango {
class Environment {
private:
  std::unordered_map<std::wstring, Data *> values =
      std::unordered_map<std::wstring, Data *>();

public:
  void define(std::wstring name, Data *value);
  Data *get(Token name);
};
}; // namespace Mango

#endif // INCLUDE_SRC_ENVIRONMENT_HPP_
