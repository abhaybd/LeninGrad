#pragma once

#include <functional>
#include <memory>
#include <vector>

namespace leningrad {
template <typename T> class DiffValue;
}

namespace leningrad::impl {

template <typename T> class Node;

template <typename T> struct Edge {
    Edge(std::shared_ptr<Node<T>> to,
         const std::function<leningrad::DiffValue<T>()> &derivativeFn)
        : to(to), derivativeFn(derivativeFn) {}

    const std::shared_ptr<Node<T>> to;
    const std::function<leningrad::DiffValue<T>()> derivativeFn;
};

template <typename T> class Node {
public:
    Node() : value(), edges() {}
    explicit Node(T value) : value(value), edges() {}
    Node(T value, const std::vector<Edge<T>> &edges)
        : value(value), edges(edges) {}

    Node(T value, const std::vector<Edge<T>> &&edges)
        : value(value), edges(edges) {}

    const T value;
    const std::vector<Edge<T>> edges;
};
} // namespace leningrad::impl
