#pragma once

#include <functional>
#include <list>
#include <memory>
#include <ostream>
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

template <typename T>
void printComputationGraphCSV(std::ostream &ostream,
                              std::shared_ptr<Node<T>> node_) {
    std::list<std::shared_ptr<Node<T>>> fringe;
    fringe.push_back(node_);

    ostream << "FromID,ToID,FromVal,ToVal,EdgeVal\n";
    while (!fringe.empty()) {
        auto node = fringe.front();
        fringe.pop_front();
        for (const impl::Edge<T> &edge : node->edges) {
            auto next = edge.to;
            DiffValue<T> derivative = edge.derivativeFn();
            fringe.push_back(next);
            ostream << node.get() << "," << next.get() << "," << node->value
                    << "," << next->value << "," << derivative.value()
                    << "\n";
        }
    }
}
} // namespace leningrad::impl
