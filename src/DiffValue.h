#pragma once

#include <memory>
#include <type_traits>

#include "ComputationGraph.h"

namespace leningrad {

template <typename T> class DiffValue {
    static_assert(std::is_floating_point<T>::value);

public:
    DiffValue(T value) // NOLINT(google-explicit-constructor)
        : node(std::make_shared<impl::Node<T>>(value)) {}

private:
    explicit DiffValue(const std::shared_ptr<impl::Node<T>> node)
        : node(node) {}
    std::shared_ptr<impl::Node<T>> node;
};
} // namespace leningrad
