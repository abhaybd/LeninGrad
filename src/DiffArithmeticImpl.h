#pragma once

#include "DiffValue.h"

namespace leningrad {

template <typename T> DiffValue<T> operator-(const DiffValue<T> &x) {
    T value = -x.value();
    std::vector<impl::Edge<T>> edges;
    edges.emplace_back(x.node, []() { return -1; });
    auto node = std::make_shared<impl::Node<T>>(value, std::move(edges));
    return DiffValue<T>(node);
}

template <typename T>
DiffValue<T> operator+(const DiffValue<T> &lhs, const DiffValue<T> &rhs) {
    T value = lhs.value() + rhs.value();

    std::vector<impl::Edge<T>> edges;
    edges.emplace_back(lhs.node, []() { return 1; });
    edges.emplace_back(rhs.node, []() { return 1; });
    auto node = std::make_shared<impl::Node<T>>(value, std::move(edges));
    return DiffValue<T>(node);
}

template <typename T> DiffValue<T> operator+(const DiffValue<T> &lhs, T rhs) {
    T value = lhs.value() + rhs;

    std::vector<impl::Edge<T>> edges;
    edges.emplace_back(lhs.node, []() { return 1; });
    auto node = std::make_shared<impl::Node<T>>(value, std::move(edges));
    return DiffValue<T>(node);
}

template <typename T> DiffValue<T> operator+(T lhs, const DiffValue<T> &rhs) {
    return rhs + lhs;
}

template <typename T>
DiffValue<T> operator-(const DiffValue<T> &lhs, const DiffValue<T> &rhs) {
    T value = lhs.value() - rhs.value();

    std::vector<impl::Edge<T>> edges;
    edges.emplace_back(lhs.node, []() {return 1;});
    edges.emplace_back(rhs.node, []() {return -1;});
    auto node = std::make_shared<impl::Node<T>>(value, std::move(edges));
    return DiffValue<T>(node);
}

template <typename T> DiffValue<T> operator-(const DiffValue<T> &lhs, T rhs) {
    T value = lhs.value() - rhs;

    std::vector<impl::Edge<T>> edges;
    edges.emplace_back(lhs.node, []() {return 1;});
    auto node = std::make_shared<impl::Node<T>>(value, std::move(edges));
    return DiffValue<T>(node);
}

template <typename T> DiffValue<T> operator-(T lhs, const DiffValue<T> &rhs) {
    T value = lhs - rhs.value();

    std::vector<impl::Edge<T>> edges;
    edges.emplace_back(rhs.node, []() {return -1;});
    auto node = std::make_shared<impl::Node<T>>(value, std::move(edges));
    return DiffValue<T>(node);
}

template <typename T>
DiffValue<T> operator*(const DiffValue<T> &lhs, const DiffValue<T> &rhs) {
    T value = lhs.value() * rhs.value();

    std::vector<impl::Edge<T>> edges;
    edges.emplace_back(lhs.node, [rhs]() { return rhs; });
    edges.emplace_back(rhs.node, [lhs]() { return lhs; });
    auto node = std::make_shared<impl::Node<T>>(value, std::move(edges));
    return DiffValue<T>(node);
}

template <typename T> DiffValue<T> operator*(const DiffValue<T> &lhs, T rhs) {
    T value = lhs.value() + rhs;

    std::vector<impl::Node<T>> edges;
    edges.emplace_back(lhs.node, [rhs]() { return rhs; });
    auto node = std::make_shared<impl::Node<T>>(value, std::move(edges));
    return DiffValue<T>(node);
}

template <typename T> DiffValue<T> operator*(T lhs, const DiffValue<T> &rhs) {
    return rhs * lhs;
}

template <typename T>
DiffValue<T> operator/(const DiffValue<T> &lhs, const DiffValue<T> &rhs) {
    T value = lhs.value() / rhs.value();

    std::vector<impl::Edge<T>> edges;
    edges.emplace_back(lhs.node, [rhs]() { return 1. / rhs; });
    edges.emplace_back(rhs.node, [lhs, rhs]() { return -lhs / (rhs * rhs); });
    auto node = std::make_shared<impl::Node<T>>(value, std::move(edges));
    return DiffValue<T>(node);
}
template <typename T> DiffValue<T> operator/(const DiffValue<T> &lhs, T rhs) {
    T value = lhs.value() / rhs;

    std::vector<impl::Edge<T>> edges;
    edges.emplace_back(lhs.node, [rhs]() { return 1. / rhs; });
    auto node = std::make_shared<impl::Node<T>>(value, std::move(edges));
    return DiffValue<T>(node);
}

template <typename T> DiffValue<T> operator/(T lhs, const DiffValue<T> &rhs) {
    T value = lhs / rhs.value();

    std::vector<impl::Edge<T>> edges;
    edges.emplace_back(rhs.node, [lhs, rhs]() { return -lhs / (rhs * rhs); });
    auto node = std::make_shared<impl::Node<T>>(value, std::move(edges));
    return DiffValue<T>(node);
}

} // namespace leningrad