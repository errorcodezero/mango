#ifndef INCLUDE_SRC_DATA_HPP_
#define INCLUDE_SRC_DATA_HPP_

#include "cstdint"
#include "string"
#include "variant"
#include <cmath>

namespace Mango {
using Data = std::variant<std::wstring, std::int32_t, std::double_t, bool>;
}

#endif // INCLUDE_SRC_DATA_HPP_
