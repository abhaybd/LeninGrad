#pragma once

#include "DiffValue.h"

namespace leningrad {
template <typename T, typename U>
bool operator==(const DiffValue<T> &lhs, const DiffValue<U> &rhs) {
    return lhs.value() == rhs.value();
}

template <typename T, typename U>
bool operator==(const DiffValue<T> &lhs, U rhs) {
    return lhs.value() == rhs;
}

template <typename T, typename U>
bool operator==(const U lhs, const DiffValue<T> &rhs) {
    return rhs == lhs;
}

template <typename T, typename U>
bool operator!=(const DiffValue<T> &lhs, const DiffValue<U> &rhs) {
    return !(lhs == rhs);
}

template <typename T, typename U>
bool operator!=(const DiffValue<T> &lhs, U rhs) {
    return !(lhs == rhs);
}

template <typename T, typename U>
bool operator!=(const U lhs, const DiffValue<T> &rhs) {
    return !(lhs == rhs);
}

template <typename T, typename U>
bool operator<(const DiffValue<T> &lhs, const DiffValue<U> &rhs) {
    return lhs.value() < rhs.value();
}

template <typename T, typename U>
bool operator<(const DiffValue<T> &lhs, U rhs) {
    return lhs.value() < rhs;
}

template <typename T, typename U>
bool operator<(U lhs, const DiffValue<T> &rhs) {
    return lhs < rhs.value();
}

template <typename T, typename U>
bool operator<=(const DiffValue<T> &lhs, const DiffValue<U> &rhs) {
    return (lhs < rhs) || (lhs == rhs);
}

template <typename T, typename U>
bool operator<=(const DiffValue<T> &lhs, U rhs) {
    return (lhs < rhs) || (lhs == rhs);
}

template <typename T, typename U>
bool operator<=(U lhs, const DiffValue<T> &rhs) {
    return (lhs < rhs) || (lhs == rhs);
}

template <typename T, typename U>
bool operator>=(const DiffValue<T> &lhs, const DiffValue<U> &rhs) {
    return !(lhs < rhs);
}

template <typename T, typename U>
bool operator>=(const DiffValue<T> &lhs, U rhs) {
    return !(lhs < rhs);
}

template <typename T, typename U>
bool operator>=(U lhs, const DiffValue<T> &rhs) {
    return !(lhs < rhs);
}

template <typename T, typename U>
bool operator>(const DiffValue<T> &lhs, const DiffValue<U> &rhs) {
    return !(lhs <= rhs);
}

template <typename T, typename U>
bool operator>(const DiffValue<T> &lhs, U rhs) {
    return !(lhs <= rhs);
}

template <typename T, typename U>
bool operator>(U lhs, const DiffValue<T> &rhs) {
    return !(lhs <= rhs);
}

template <typename T> DiffValue<T> max(const DiffValue<T> &x, const DiffValue<T> &y) {
    return x > y ? x : y;
}

template <typename T, typename U> DiffValue<T> max(const DiffValue<T> &x, U y) {
    return x > y ? x : y;
}

template <typename T, typename U> DiffValue<T> max(U x, const DiffValue<T> &y) {
    return x > y ? x : y;
}

template <typename T> DiffValue<T> min(const DiffValue<T> &x, const DiffValue<T> &y) {
    return x < y ? x : y;
}

template <typename T, typename U> DiffValue<T> min(const DiffValue<T> &x, U y) {
    return x < y ? x : y;
}

template <typename T, typename U> DiffValue<T> min(U x, const DiffValue<T> &y) {
    return x < y ? x : y;
}

} // namespace leningrad
