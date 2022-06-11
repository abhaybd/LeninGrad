#pragma once

namespace leningrad {

template <typename T> class DiffValue;

template <typename T> DiffValue<T> operator-(const DiffValue<T> &x);

template <typename T>
DiffValue<T> operator+(const DiffValue<T> &lhs, const DiffValue<T> &rhs);

template <typename T> DiffValue<T> operator+(const DiffValue<T> &lhs, T rhs);

template <typename T> DiffValue<T> operator+(T lhs, const DiffValue<T> &rhs);

template <typename T>
DiffValue<T> operator-(const DiffValue<T> &lhs, const DiffValue<T> &rhs);

template <typename T> DiffValue<T> operator-(const DiffValue<T> &lhs, T rhs);

template <typename T> DiffValue<T> operator-(T lhs, const DiffValue<T> &rhs);

template <typename T>
DiffValue<T> operator*(const DiffValue<T> &lhs, const DiffValue<T> &rhs);

template <typename T> DiffValue<T> operator*(const DiffValue<T> &lhs, T rhs);

template <typename T> DiffValue<T> operator*(T lhs, const DiffValue<T> &rhs);

template <typename T>
DiffValue<T> operator/(const DiffValue<T> &lhs, const DiffValue<T> &rhs);
template <typename T> DiffValue<T> operator/(const DiffValue<T> &lhs, T rhs);

template <typename T> DiffValue<T> operator/(T lhs, const DiffValue<T> &rhs);

} // namespace leningrad