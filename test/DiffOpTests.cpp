#include <catch2/catch.hpp>

#include <functional>
#include <vector>
#include <cmath>
#include <string>
#include <tuple>

#include "../src/Core.h"

using namespace leningrad;

constexpr double eps = 1e-6;

double numericalDifferentiate(const std::function<double(double)>& fn, double x) {
    return (fn(x+eps) - fn(x-eps)) / (2 *eps);
}

TEST_CASE("Test pow", "[DiffOp]") {
    ddouble x = 3;
    ddouble y = pow(x, 2);
    ddouble dydx = differentiate(y).wrt(x); // TODO: figure out why garbage (near zero) is being returned. Is something being deallocated? Is the derivative fn of the pow function wrong? that feels most likely.
    REQUIRE(dydx.value() == Approx(6));
}

TEST_CASE("Test univariate funcs over R", "[DiffOp]") {
    std::vector<std::tuple<std::string,
                           std::function<ddouble(const ddouble &)>,
                          std::function<double(double)>>>
        funcs;
    // exclude all functions with a limited domain
    funcs.emplace_back("abs", leningrad::abs<double>, [](double x){return std::abs(x);});
    funcs.emplace_back("exp", leningrad::exp<double>, [](double x){return std::exp(x);});
    funcs.emplace_back("square", leningrad::square<double>, [](double x){return std::pow(x, 2);});
    funcs.emplace_back("sin", leningrad::sin<double>, [](double x){return std::sin(x);});
    funcs.emplace_back("cos", leningrad::cos<double>, [](double x){return std::cos(x);});
    funcs.emplace_back("tan", leningrad::tan<double>, [](double x){return std::tan(x);});
    funcs.emplace_back("csc", leningrad::csc<double>, [](double x){return 1.0/std::sin(x);});
    funcs.emplace_back("sec", leningrad::sec<double>, [](double x){return 1.0/std::cos(x);});
    funcs.emplace_back("cot", leningrad::cot<double>, [](double x){return 1.0/std::tan(x);});
    funcs.emplace_back("atan", leningrad::atan<double>, [](double x){return std::atan(x);});
    funcs.emplace_back("sinh", leningrad::sinh<double>, [](double x){return std::sinh(x);});
    funcs.emplace_back("cosh", leningrad::cosh<double>, [](double x){return std::cosh(x);});
    funcs.emplace_back("tanh", leningrad::tanh<double>, [](double x){return std::tanh(x);});
    funcs.emplace_back("asinh", leningrad::asinh<double>, [](double x){return std::asinh(x);});
    funcs.emplace_back("erf", leningrad::erf<double>, [](double x){return std::erf(x);});
    funcs.emplace_back("erfc", leningrad::erfc<double>, [](double x){return std::erfc(x);});

    std::vector<double> points{
        0.1, 1, -1, 3.5, -3.5
    };

    for (const auto &tuple : funcs) {
        std::string name = std::get<0>(tuple);
        std::function<ddouble(const ddouble &)> diffFn = std::get<1>(tuple);
        std::function<double(double)> fn = std::get<2>(tuple);
        for (double p : points) {
            ddouble x = p;
            ddouble y = diffFn(x);
            double dydx = differentiate(y).wrt(x).value();
            double dydxTrue = numericalDifferentiate(fn, p);
            INFO("Testing function: " << name << " at x=" << p);
            REQUIRE(dydx == Approx(dydxTrue));
        }
    }
}
