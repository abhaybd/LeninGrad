#pragma once

#include "DiffValue.h"

#include <list>
#include <memory>
#include <unordered_map>

namespace leningrad {

template <typename T> class DerivativeResult {
public:
    explicit DerivativeResult(
        const std::unordered_map<std::shared_ptr<impl::Node<T>>, DiffValue<T>>
            &derivativeMap)
        : derivativeMap(derivativeMap) {}

    DiffValue<T> wrt(const DiffValue<T> &value) {
        auto itr = derivativeMap.find(value.node);
        return itr != derivativeMap.end() ? itr->second : 0;
    }

    bool hasDerivative(const DiffValue<T> &value) {
        return derivativeMap.find(value.node) != derivativeMap.end();
    }

private:
    std::unordered_map<std::shared_ptr<impl::Node<T>>, DiffValue<T>>
        derivativeMap;
};

template <typename T>
DerivativeResult<T> differentiate(DiffValue<T> value, unsigned int order) {
    assert(order > 0 && "Cannot take 0-order derivative!");

    std::list<std::shared_ptr<impl::Node<T>>> fringe{value.node};
    std::unordered_map<std::shared_ptr<impl::Node<T>>, DiffValue<T>>
        derivativeMap;
    derivativeMap.insert({value.node, 1.0});
    while (!fringe.empty()) {
        auto node = fringe.front();
        fringe.pop_front();
        DiffValue<T> nodeDerivative = derivativeMap.at(node);
        for (const impl::Edge<T> &edge : node->edges) {
            auto next = edge.to;
            DiffValue<T> intermediateDerivative = edge.derivativeFn();
            derivativeMap.insert({next, 0});
            derivativeMap.at(next) += intermediateDerivative * nodeDerivative;
            fringe.push_back(next);
        }
    }
    return DerivativeResult<T>(derivativeMap);
}

} // namespace leningrad