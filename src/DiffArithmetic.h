#pragma once

#include "DiffValue.h"

namespace leningrad {

template <typename T> DiffValue<T> operator-(const DiffValue<T> &x) {
    T value = -x.value();
    std::vector<impl::Edge<T>> edges;
    edges.emplace_back(impl::getDiffValueNode(x), []() { return -1; });
    auto node = std::make_shared<impl::Node<T>>(value, std::move(edges));
    return impl::createDiffValueFromNode(node);
}

template <typename T>
DiffValue<T> operator+(const DiffValue<T> &lhs, const DiffValue<T> &rhs) {
    T value = lhs.value() + rhs.value();

    std::vector<impl::Edge<T>> edges;
    edges.emplace_back(impl::getDiffValueNode(lhs), []() { return 1; });
    edges.emplace_back(impl::getDiffValueNode(rhs), []() { return 1; });
    auto node = std::make_shared<impl::Node<T>>(value, std::move(edges));
    return impl::createDiffValueFromNode(node);
}

template <typename T, typename U>
DiffValue<T> operator+(const DiffValue<T> &lhs, U rhs) {
    T value = lhs.value() + rhs;

    std::vector<impl::Edge<T>> edges;
    edges.emplace_back(impl::getDiffValueNode(lhs), []() { return 1; });
    auto node = std::make_shared<impl::Node<T>>(value, std::move(edges));
    return impl::createDiffValueFromNode(node);
}

template <typename T, typename U>
DiffValue<T> operator+(U lhs, const DiffValue<T> &rhs) {
    return rhs + lhs;
}

template <typename T>
DiffValue<T> operator-(const DiffValue<T> &lhs, const DiffValue<T> &rhs) {
    T value = lhs.value() - rhs.value();

    std::vector<impl::Edge<T>> edges;
    edges.emplace_back(impl::getDiffValueNode(lhs), []() { return 1; });
    edges.emplace_back(impl::getDiffValueNode(rhs), []() { return -1; });
    auto node = std::make_shared<impl::Node<T>>(value, std::move(edges));
    return impl::createDiffValueFromNode(node);
}

template <typename T, typename U>
DiffValue<T> operator-(const DiffValue<T> &lhs, U rhs) {
    T value = lhs.value() - rhs;

    std::vector<impl::Edge<T>> edges;
    edges.emplace_back(impl::getDiffValueNode(lhs), []() { return 1; });
    auto node = std::make_shared<impl::Node<T>>(value, std::move(edges));
    return impl::createDiffValueFromNode(node);
}

template <typename T, typename U>
DiffValue<T> operator-(U lhs, const DiffValue<T> &rhs) {
    T value = lhs - rhs.value();

    std::vector<impl::Edge<T>> edges;
    edges.emplace_back(impl::getDiffValueNode(rhs), []() { return -1; });
    auto node = std::make_shared<impl::Node<T>>(value, std::move(edges));
    return impl::createDiffValueFromNode(node);
}

template <typename T>
DiffValue<T> operator*(const DiffValue<T> &lhs, const DiffValue<T> &rhs) {
    T value = lhs.value() * rhs.value();

    std::vector<impl::Edge<T>> edges;
    edges.emplace_back(impl::getDiffValueNode(lhs), [rhs]() { return rhs; });
    edges.emplace_back(impl::getDiffValueNode(rhs), [lhs]() { return lhs; });
    auto node = std::make_shared<impl::Node<T>>(value, std::move(edges));
    return impl::createDiffValueFromNode(node);
}

template <typename T, typename U>
DiffValue<T> operator*(const DiffValue<T> &lhs, U rhs) {
    T value = lhs.value() * rhs;

    std::vector<impl::Edge<T>> edges;
    edges.emplace_back(impl::getDiffValueNode(lhs), [rhs]() { return rhs; });
    auto node = std::make_shared<impl::Node<T>>(value, std::move(edges));
    return impl::createDiffValueFromNode(node);
}

template <typename T, typename U>
DiffValue<T> operator*(U lhs, const DiffValue<T> &rhs) {
    return rhs * lhs;
}

template <typename T>
DiffValue<T> operator/(const DiffValue<T> &lhs, const DiffValue<T> &rhs) {
    T value = lhs.value() / rhs.value();

    std::vector<impl::Edge<T>> edges;
    edges.emplace_back(impl::getDiffValueNode(lhs),
                       [rhs]() { return static_cast<T>(1) / rhs; });
    edges.emplace_back(impl::getDiffValueNode(rhs),
                       [lhs, rhs]() { return -lhs / (rhs * rhs); });
    auto node = std::make_shared<impl::Node<T>>(value, std::move(edges));
    return impl::createDiffValueFromNode(node);
}

template <typename T, typename U>
DiffValue<T> operator/(const DiffValue<T> &lhs, U rhs) {
    T value = lhs.value() / rhs;

    std::vector<impl::Edge<T>> edges;
    edges.emplace_back(impl::getDiffValueNode(lhs),
                       [rhs]() { return static_cast<T>(1) / rhs; });
    auto node = std::make_shared<impl::Node<T>>(value, std::move(edges));
    return impl::createDiffValueFromNode(node);
}

template <typename T, typename U>
DiffValue<T> operator/(U lhs, const DiffValue<T> &rhs) {
    T value = lhs / rhs.value();

    std::vector<impl::Edge<T>> edges;
    edges.emplace_back(impl::getDiffValueNode(rhs),
                       [lhs, rhs]() { return -lhs / (rhs * rhs); });
    auto node = std::make_shared<impl::Node<T>>(value, std::move(edges));
    return impl::createDiffValueFromNode(node);
}

} // namespace leningrad