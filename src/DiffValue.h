#pragma once

#include <memory>
#include <type_traits>

#include "ComputationGraph.h"
#include "DiffOps.h"

namespace leningrad {

template <typename T> class DiffValue {
    static_assert(std::is_floating_point<T>::value);

public:
    DiffValue(T value) // NOLINT(google-explicit-constructor)
        : node(std::make_shared<impl::Node<T>>(value)) {}

    T value() const { return node->value; }

private:
    explicit DiffValue(const std::shared_ptr<impl::Node<T>> node)
        : node(node) {}
    std::shared_ptr<impl::Node<T>> node;

    friend DiffValue operator-<T>(const DiffValue &x);

    friend DiffValue operator+<T>(const DiffValue &lhs,
                                  const DiffValue &rhs);
    friend DiffValue operator+<T>(const DiffValue &lhs, T rhs);
    friend DiffValue operator-<T>(const DiffValue &lhs,
                                  const DiffValue &rhs);
    friend DiffValue operator-<T>(const DiffValue &lhs, T rhs);
    friend DiffValue operator*<T>(const DiffValue &lhs,
                                  const DiffValue &rhs);
    friend DiffValue operator*<T>(const DiffValue &lhs, T rhs);
    friend DiffValue operator/<T>(const DiffValue &lhs,
                                  const DiffValue &rhs);
    friend DiffValue operator/<T>(const DiffValue &lhs, T rhs);
    friend DiffValue operator/<T>(T lhs, const DiffValue &rhs);
};
} // namespace leningrad
