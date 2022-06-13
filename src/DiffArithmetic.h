#pragma once

namespace leningrad {

template <typename T> class DiffValue;

// The following are forward declarations for methods in DiffArithmeticImpl.h,
// which allows them to be befriended by DiffValue

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
