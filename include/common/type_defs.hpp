#pragma once

#include <type_traits>

template<typename T> concept NumericType = std::is_arithmetic_v<T>;

template<typename T> concept EnumType = std::is_enum_v<T>;
