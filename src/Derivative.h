#pragma once

#include "DiffValue.h"

#include <initializer_list>
#include <list>
#include <memory>
#include <unordered_map>
#include <iostream>

namespace leningrad {

template <typename T> class DerivativeResult {
public:
    explicit DerivativeResult(
        const std::unordered_map<std::shared_ptr<impl::Node<T>>, DiffValue<T>>
            &derivativeMap)
        : derivativeMap(derivativeMap) {}

    DiffValue<T> wrt(const DiffValue<T> &value) {
        auto itr = derivativeMap.find(impl::getDiffValueNode(value));
        return itr != derivativeMap.end() ? itr->second : 0;
    }

    bool hasDerivative(const DiffValue<T> &value) {
        return derivativeMap.find(impl::getDiffValueNode(value)) !=
               derivativeMap.end();
    }

private:
    std::unordered_map<std::shared_ptr<impl::Node<T>>, DiffValue<T>>
        derivativeMap;
};

template <typename T>
DerivativeResult<T> differentiate(const DiffValue<T> &value) {
    std::list<std::shared_ptr<impl::Node<T>>> fringe{
        impl::getDiffValueNode(value)};
    std::unordered_map<std::shared_ptr<impl::Node<T>>, DiffValue<T>>
        derivativeMap;
    derivativeMap.insert({impl::getDiffValueNode(value), 1.0});
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

template <typename T>
DiffValue<T> differentiate(const DiffValue<T> &value, const DiffValue<T> &x,
                           unsigned int order) {
    DiffValue<T> derivative = value;
    for (int i = 0; i < order; i++) {
        derivative = differentiate(derivative).wrt(x);
    }
    return derivative;
}

template <typename T>
DiffValue<T> differentiate(const DiffValue<T> &value,
                           const std::initializer_list<DiffValue<T>> &wrt) {
    return differentiate(value, wrt.begin(), wrt.end());
}

template <typename T, typename It>
DiffValue<T> differentiate(const DiffValue<T> &value, const It &wrtBegin,
                           const It &wrtEnd) {
    DiffValue<T> derivative = value;
    int i = 0;
    for (auto it = wrtBegin; it != wrtEnd; it++) {
        std::cout << "\n========== " << i++ <<"-th derivative ==========" << std::endl;
//        impl::printComputationGraphCSV(std::cout, impl::getDiffValueNode(derivative));
//        std::cout << std::endl;
        derivative = differentiate(derivative).wrt(*it);
    }
//    std::cout << "\n========== " << i++ <<"-th derivative ==========\n";
//    impl::printComputationGraphCSV(std::cout, impl::getDiffValueNode(derivative));
//    std::cout << std::endl;
    return derivative;
}

} // namespace leningrad
