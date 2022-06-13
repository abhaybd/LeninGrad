#pragma once

#include <memory>
#include <string>
#include <type_traits>

#include "ComputationGraph.h"

namespace leningrad {

template <typename T> class DiffValue;

template <typename T> class DerivativeResult;

template <typename T>
DerivativeResult<T> differentiate(DiffValue<T> value, unsigned int order = 1);

namespace impl {
template <typename T> std::shared_ptr<impl::Node<T>> getDiffValueNode(const DiffValue<T> &value);
template <typename T> DiffValue<T> createDiffValueFromNode(const std::shared_ptr<Node<T>> &node);
} // namespace impl

template <typename T> class DiffValue {
    static_assert(std::is_floating_point<T>::value);

public:
    DiffValue() : node(std::make_shared<impl::Node<T>>()) {}

    DiffValue(T value) // NOLINT(google-explicit-constructor)
        : node(std::make_shared<impl::Node<T>>(value)) {}

    T value() const { return node->value; }

    DiffValue &operator+=(const DiffValue &rhs) {
        *this = *this + rhs;
        return *this;
    }

    DiffValue &operator+=(T rhs) {
        *this = *this + rhs;
        return *this;
    }

    DiffValue &operator-=(const DiffValue &rhs) {
        *this = *this - rhs;
        return *this;
    }

    DiffValue &operator-=(T rhs) {
        *this = *this - rhs;
        return *this;
    }

    DiffValue &operator*=(const DiffValue &rhs) {
        *this = *this * rhs;
        return *this;
    }

    DiffValue &operator*=(T rhs) {
        *this = *this * rhs;
        return *this;
    }

    DiffValue &operator/=(const DiffValue &rhs) {
        *this = *this / rhs;
        return *this;
    }

    DiffValue &operator/=(T rhs) {
        *this = *this / rhs;
        return *this;
    }

private:
    explicit DiffValue(const std::shared_ptr<impl::Node<T>> &node)
        : node(node) {}
    std::shared_ptr<impl::Node<T>> node;

    friend DerivativeResult<T> differentiate<T>(DiffValue value,
                                                unsigned int order);
    friend class DerivativeResult<T>;

    friend std::shared_ptr<impl::Node<T>> impl::getDiffValueNode<T>(const DiffValue<T> &value);

    friend DiffValue
    impl::createDiffValueFromNode<T>(const std::shared_ptr<impl::Node<T>> &node);
};

namespace impl {
template <typename T> std::shared_ptr<Node<T>> getDiffValueNode(const DiffValue<T> &value) {
    return value.node;
}

template <typename T>
DiffValue<T> createDiffValueFromNode(const std::shared_ptr<Node<T>> &node) {
    return DiffValue<T>(node);
}
} // namespace impl
} // namespace leningrad
