#pragma once

#include <cmath>
#include <memory>
#include <vector>

#include "ComputationGraph.h"
#include "DiffValue.h"

namespace leningrad {

template <typename T> DiffValue<T> abs(const DiffValue<T> &x) {
    T value = std::abs(x.value());

    std::vector<impl::Edge<T>> edges;
    edges.emplace_back(impl::getDiffValueNode(x),
                       [x]() { return x >= 0 ? 1 : -1; });
    auto node = std::make_shared<impl::Node<T>>(value, std::move(edges));
    return impl::createDiffValueFromNode(node);
}

template <typename T>
DiffValue<T> log(const DiffValue<T> &base, const DiffValue<T> &x) {
    T value = std::log(x.value()) / std::log(base.value());

    std::vector<impl::Edge<T>> edges;
    edges.emplace_back(impl::getDiffValueNode(base), [base, x]() {
        return -log(base, x) / (base * log(base));
    });
    edges.emplace_back(impl::getDiffValueNode(x),
                       [x]() { return static_cast<T>(1) / x; });
    auto node = std::make_shared<impl::Node<T>>(value, std::move(edges));
    return impl::createDiffValueFromNode(node);
}

template <typename T, typename U>
DiffValue<T> log(const DiffValue<T> &base, U x) {
    T value = std::log(x) / std::log(base.value());

    std::vector<impl::Edge<T>> edges;
    edges.emplace_back(impl::getDiffValueNode(base), [base, x]() {
        return -log(base, x) / (base * log(base));
    });
    auto node = std::make_shared<impl::Node<T>>(value, std::move(edges));
    return impl::createDiffValueFromNode(node);
}

template <typename T, typename U>
DiffValue<T> log(U base, const DiffValue<T> &x) {
    T value = std::log(x.value()) / std::log(base);

    std::vector<impl::Edge<T>> edges;
    edges.emplace_back(impl::getDiffValueNode(x),
                       [x]() { return static_cast<T>(1) / x; });
    auto node = std::make_shared<impl::Node<T>>(value, std::move(edges));
    return impl::createDiffValueFromNode(node);
}

template <typename T> DiffValue<T> log(const DiffValue<T> &x) {
    return log(static_cast<T>(M_E), x);
}

template <typename T> DiffValue<T> log10(const DiffValue<T> &x) {
    return log(10, x);
}

template <typename T> DiffValue<T> log2(const DiffValue<T> &x) {
    return log(2, x);
}

template <typename T> DiffValue<T> sqrt(const DiffValue<T> &x) {
    T value = std::sqrt(x.value());

    std::vector<impl::Edge<T>> edges;
    edges.emplace_back(impl::getDiffValueNode(x), [x]() { return 1 / (2 * sqrt(x)); });
    auto node = std::make_shared<impl::Node<T>>(value, std::move(edges));
    return impl::createDiffValueFromNode(node);
}

template <typename T>
DiffValue<T> pow(const DiffValue<T> &lhs, const DiffValue<T> &rhs) {
    T value = rhs.value() == 0 ? 1 : std::pow(lhs.value(), rhs.value());

    std::vector<impl::Edge<T>> edges;
    if (rhs.value() == 0) {
        edges.emplace_back(impl::getDiffValueNode(lhs), []() { return 0; });
    } else {
        edges.emplace_back(impl::getDiffValueNode(lhs), [lhs, rhs]() {
            return pow(lhs, rhs - static_cast<T>(1)) * rhs;
        });
    }
    edges.emplace_back(impl::getDiffValueNode(rhs),
                       [lhs, rhs]() { return log(lhs) * pow(lhs, rhs); });
    auto node = std::make_shared<impl::Node<T>>(value, std::move(edges));
    return impl::createDiffValueFromNode(node);
}

template <typename T, typename U>
DiffValue<T> pow(const DiffValue<T> &lhs, U rhs) {
    T value = rhs == 0 ? 1 : std::pow(lhs.value(), rhs);

    std::vector<impl::Edge<T>> edges;
    if (rhs == 0) {
        edges.emplace_back(impl::getDiffValueNode(lhs), []() { return 0; });
    } else {
        edges.emplace_back(impl::getDiffValueNode(lhs), [lhs, rhs]() {
            return pow(lhs, rhs - 1) * rhs;
        });
    }
    auto node = std::make_shared<impl::Node<T>>(value, std::move(edges));
    return impl::createDiffValueFromNode(node);
}

template <typename T, typename U>
DiffValue<T> pow(U lhs, const DiffValue<T> &rhs) {
    T value = rhs.value() == 0 ? 1 : std::pow(lhs, rhs.value());

    std::vector<impl::Edge<T>> edges;
    edges.emplace_back(impl::getDiffValueNode(rhs),
                       [lhs, rhs]() { return std::log(lhs) * pow(lhs, rhs); });
    auto node = std::make_shared<impl::Node<T>>(value, std::move(edges));
    return impl::createDiffValueFromNode(node);
}

template <typename T> DiffValue<T> square(const DiffValue<T> x) {
    return pow(x, 2);
}

template <typename T>
DiffValue<T> hypot(const DiffValue<T> &x, const DiffValue<T> &y) {
    return sqrt(x * x + y * y);
}

template <typename T, typename U>
DiffValue<T> hypot(const DiffValue<T> &x, U y) {
    return sqrt(x * x + y * y);
}

template <typename T, typename U>
DiffValue<T> hypot(U x, const DiffValue<T> &y) {
    return sqrt(x * x + y * y);
}

template <typename T> DiffValue<T> exp(const DiffValue<T> &x) {
    return pow(static_cast<T>(M_E), x);
}

template <typename T> DiffValue<T> cos(const DiffValue<T> &x);

template <typename T> DiffValue<T> sin(const DiffValue<T> &x) {
    T value = std::sin(x.value());

    std::vector<impl::Edge<T>> edges;
    edges.emplace_back(impl::getDiffValueNode(x), [x]() { return cos(x); });
    auto node = std::make_shared<impl::Node<T>>(value, std::move(edges));
    return impl::createDiffValueFromNode(node);
}

template <typename T> DiffValue<T> cos(const DiffValue<T> &x) {
    T value = std::cos(x.value());

    std::vector<impl::Edge<T>> edges;
    edges.emplace_back(impl::getDiffValueNode(x), [x]() { return -sin(x); });
    auto node = std::make_shared<impl::Node<T>>(value, std::move(edges));
    return impl::createDiffValueFromNode(node);
}

template <typename T> DiffValue<T> sec(const DiffValue<T> &x) {
    return static_cast<T>(1) / cos(x);
}

template <typename T> DiffValue<T> csc(const DiffValue<T> &x) {
    return static_cast<T>(1) / sin(x);
}

template <typename T> DiffValue<T> tan(const DiffValue<T> &x) {
    T value = std::tan(x.value());

    std::vector<impl::Edge<T>> edges;
    edges.emplace_back(impl::getDiffValueNode(x),
                       [x]() { return pow(sec(x), 2); });
    auto node = std::make_shared<impl::Node<T>>(value, std::move(edges));
    return impl::createDiffValueFromNode(node);
}

template <typename T> DiffValue<T> cot(const DiffValue<T> &x) {
    return static_cast<T>(1) / tan(x);
}

template <typename T> DiffValue<T> acos(const DiffValue<T> &x) {
    T value = std::acos(x.value());

    std::vector<impl::Edge<T>> edges;
    edges.emplace_back(impl::getDiffValueNode(x),
                       [x]() { return -1 / sqrt(1 - x * x); });
    auto node = std::make_shared<impl::Node<T>>(value, std::move(edges));
    return impl::createDiffValueFromNode(node);
}

template <typename T> DiffValue<T> asin(const DiffValue<T> &x) {
    T value = std::asin(x.value());

    std::vector<impl::Edge<T>> edges;
    edges.emplace_back(impl::getDiffValueNode(x),
                       [x]() { return 1 / sqrt(1 - x * x); });
    auto node = std::make_shared<impl::Node<T>>(value, std::move(edges));
    return impl::createDiffValueFromNode(node);
}

template <typename T> DiffValue<T> atan(const DiffValue<T> &x) {
    T value = std::atan(x.value());

    std::vector<impl::Edge<T>> edges;
    edges.emplace_back(impl::getDiffValueNode(x),
                       [x]() { return 1 / (1 + x * x); });
    auto node = std::make_shared<impl::Node<T>>(value, std::move(edges));
    return impl::createDiffValueFromNode(node);
}

template <typename T>
DiffValue<T> atan2(const DiffValue<T> &y, const DiffValue<T> &x) {
    if (x > 0) {
        return atan(y / x);
    }
    if (x < 0 && y >= 0) {
        return atan(y / x) + static_cast<T>(M_PI);
    }
    if (x < 0 && y < 0) {
        return atan(y / x) - static_cast<T>(M_PI);
    }
    if (x == 0 && y > 0) {
        return M_PI / 2;
    }
    if (x == 0 && y < 0) {
        return -M_PI / 2;
    }
    return NAN;
}

template <typename T> DiffValue<T> sinh(const DiffValue<T> &x);

template <typename T> DiffValue<T> cosh(const DiffValue<T> &x) {
    T value = (std::exp(x.value()) + std::exp(-x.value())) / static_cast<T>(2);

    std::vector<impl::Edge<T>> edges;
    edges.emplace_back(impl::getDiffValueNode(x), [x]() { return sinh(x); });
    auto node = std::make_shared<impl::Node<T>>(value, std::move(edges));
    return impl::createDiffValueFromNode(node);
}

template <typename T> DiffValue<T> sinh(const DiffValue<T> &x) {
    T value = (std::exp(x.value()) - std::exp(-x.value())) / static_cast<T>(2);

    std::vector<impl::Edge<T>> edges;
    edges.emplace_back(impl::getDiffValueNode(x), [x]() { return cosh(x); });
    auto node = std::make_shared<impl::Node<T>>(value, std::move(edges));
    return impl::createDiffValueFromNode(node);
}

template <typename T> DiffValue<T> tanh(const DiffValue<T> &x) {
    return sinh(x) / cosh(x);
}

template <typename T> DiffValue<T> acosh(const DiffValue<T> &x) {
    T value = std::acosh(x.value());

    std::vector<impl::Edge<T>> edges;
    edges.emplace_back(impl::getDiffValueNode(x),
                       [x]() { return 1 / sqrt(x * x - 1); });
    auto node = std::make_shared<impl::Node<T>>(value, std::move(edges));
    return impl::createDiffValueFromNode(node);
}

template <typename T> DiffValue<T> asinh(const DiffValue<T> &x) {
    T value = std::acosh(x.value());

    std::vector<impl::Edge<T>> edges;
    edges.emplace_back(impl::getDiffValueNode(x),
                       [x]() { return 1 / sqrt(x * x + 1); });
    auto node = std::make_shared<impl::Node<T>>(value, std::move(edges));
    return impl::createDiffValueFromNode(node);
}

template <typename T> DiffValue<T> atanh(const DiffValue<T> &x) {
    T value = std::atanh(x.value());

    std::vector<impl::Edge<T>> edges;
    edges.emplace_back(impl::getDiffValueNode(x),
                       [x]() { return 1 / (1 - x * x); });
    auto node = std::make_shared<impl::Node<T>>(value, std::move(edges));
    return impl::createDiffValueFromNode(node);
}

template <typename T> DiffValue<T> erf(const DiffValue<T> &x) {
    T value = std::erf(x.value());

    std::vector<impl::Edge<T>> edges;
    edges.emplace_back(impl::getDiffValueNode(x),
                       [x]() { return 2 * exp(-x * x) / std::sqrt(M_PI); });
    auto node = std::make_shared<impl::Node<T>>(value, std::move(edges));
    return impl::createDiffValueFromNode(node);
}

template <typename T> DiffValue<T> erfc(const DiffValue<T> &x) {
    T value = std::erfc(x.value());

    std::vector<impl::Edge<T>> edges;
    edges.emplace_back(impl::getDiffValueNode(x),
                       [x]() { return -2 * exp(-x * x) / std::sqrt(M_PI); });
    auto node = std::make_shared<impl::Node<T>>(value, std::move(edges));
    return impl::createDiffValueFromNode(node);
}

template <typename T>
DiffValue<T> copysign(const DiffValue<T> &mag, const DiffValue<T> &sgn) {
    T value = std::copysign(mag.value(), sgn.value());

    std::vector<impl::Edge<T>> edges;
    edges.emplace_back(impl::getDiffValueNode(mag),
                       [sgn]() { return std::signbit(sgn.value()) ? -1 : 1; });
    auto node = std::make_shared<impl::Node<T>>(value, std::move(edges));
    return impl::createDiffValueFromNode(node);
}

template <typename T, typename U>
DiffValue<T> copysign(const DiffValue<T> &mag, U sgn) {
    T value = std::copysign(mag.value(), sgn);

    std::vector<impl::Edge<T>> edges;
    edges.emplace_back(impl::getDiffValueNode(mag),
                       [sgn]() { return std::signbit(sgn) ? -1 : 1; });
    auto node = std::make_shared<impl::Node<T>>(value, std::move(edges));
    return impl::createDiffValueFromNode(node);
}

} // namespace leningrad
