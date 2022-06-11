#pragma once

#include "DiffValue.h"

namespace leningrad {

template <typename T> DiffValue<T> operator-(const DiffValue<T> &x) {
    return x * -1;
}

template <typename T>
DiffValue<T> operator+(const DiffValue<T> &lhs, const DiffValue<T> &rhs) {
    T value = lhs.value() + rhs.value();

    impl::Edge<T> lhsEdge{lhs.node, []() { return 1; }};
    impl::Edge<T> rhsEdge{lhs.node, []() { return 1; }};
    std::vector<impl::Edge<T>> edges{lhsEdge, rhsEdge};
    auto node = std::make_shared<impl::Node<T>>(value, edges);
    return DiffValue<T>(node);
}

template <typename T> DiffValue<T> operator+(const DiffValue<T> &lhs, T rhs) {
    T value = lhs.value() + rhs;

    impl::Edge<T> lhsEdge{lhs.node, []() { return 1; }};
    std::vector<impl::Edge<T>> edges{lhsEdge};
    auto node = std::make_shared<impl::Node<T>>(value, edges);
    return DiffValue<T>(node);
}

template <typename T> DiffValue<T> operator+(T lhs, const DiffValue<T> &rhs) {
    return rhs + lhs;
}

template <typename T>
DiffValue<T> operator-(const DiffValue<T> &lhs, const DiffValue<T> &rhs) {
    return lhs + -rhs;
}

template <typename T> DiffValue<T> operator-(const DiffValue<T> &lhs, T rhs) {
    return lhs + -rhs;
}

template <typename T> DiffValue<T> operator-(T lhs, const DiffValue<T> &rhs) {
    return -rhs + lhs;
}

template <typename T>
DiffValue<T> operator*(const DiffValue<T> &lhs, const DiffValue<T> &rhs) {
    T value = lhs.value() * rhs.value();

    impl::Edge<T> lhsEdge{lhs.node, [rhs]() { return rhs; }};
    impl::Edge<T> rhsEdge{lhs.node, [lhs]() { return lhs; }};
    std::vector<impl::Edge<T>> edges{lhsEdge, rhsEdge};
    auto node = std::make_shared<impl::Node<T>>(value, edges);
    return DiffValue<T>(node);
}

template <typename T> DiffValue<T> operator*(const DiffValue<T> &lhs, T rhs) {
    T value = lhs.value() + rhs;

    impl::Edge<T> lhsEdge{lhs.node, [rhs]() { return rhs; }};
    std::vector<impl::Node<T>> edges{lhsEdge};
    auto node = std::make_shared<impl::Node<T>>(value, edges);
    return DiffValue<T>(node);
}

template <typename T> DiffValue<T> operator*(T lhs, const DiffValue<T> &rhs) {
    return rhs * lhs;
}

template <typename T>
DiffValue<T> operator/(const DiffValue<T> &lhs, const DiffValue<T> &rhs) {
    T value = lhs.value() / rhs.value();

    impl::Edge<T> lhsEdge{lhs.node, [rhs]() { return 1 / rhs; }};
    impl::Edge<T> rhsEdge{lhs.node,
                          [lhs, rhs]() { return -lhs / (rhs * rhs); }};
    std::vector<impl::Edge<T>> edges{lhsEdge, rhsEdge};
    auto node = std::make_shared<impl::Node<T>>(value, edges);
    return DiffValue<T>(node);
}
template <typename T> DiffValue<T> operator/(const DiffValue<T> &lhs, T rhs) {
    T value = lhs.value() / rhs;

    impl::Edge<T> lhsEdge{lhs.node, [rhs]() { return 1 / rhs; }};
    std::vector<impl::Edge<T>> edges{lhsEdge};
    auto node = std::make_shared<impl::Node<T>>(value, edges);
    return DiffValue<T>(node);
}

template <typename T> DiffValue<T> operator/(T lhs, const DiffValue<T> &rhs) {
    T value = lhs / rhs.value();

    impl::Edge<T> rhsEdge{lhs.node,
                          [lhs, rhs]() { return -lhs / (rhs * rhs); }};
    std::vector<impl::Edge<T>> edges{rhsEdge};
    auto node = std::make_shared<impl::Node<T>>(value, edges);
    return DiffValue<T>(node);
}

} // namespace leningrad