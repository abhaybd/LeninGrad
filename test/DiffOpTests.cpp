#include <catch2/catch.hpp>

#include <cmath>
#include <functional>
#include <string>
#include <tuple>
#include <vector>

#include "../src/Core.h"

using namespace leningrad;

constexpr double eps = 1e-10;

double numericalDifferentiate(const std::function<double(double)> &fn,
                              double x) {
    return (fn(x + eps) - fn(x - eps)) / (2 * eps);
}

TEST_CASE("Test univariate funcs over R", "[DiffOp]") {
    std::vector<std::tuple<std::string, std::function<ddouble(const ddouble &)>,
                           std::function<double(double)>>>
        funcs;
    // exclude all functions with a limited domain
    funcs.emplace_back("abs", leningrad::abs<double>,
                       [](double x) { return std::abs(x); });
    funcs.emplace_back("exp", leningrad::exp<double>,
                       [](double x) { return std::exp(x); });
    funcs.emplace_back("square", leningrad::square<double>,
                       [](double x) { return std::pow(x, 2); });
    funcs.emplace_back("sin", leningrad::sin<double>,
                       [](double x) { return std::sin(x); });
    funcs.emplace_back("cos", leningrad::cos<double>,
                       [](double x) { return std::cos(x); });
    funcs.emplace_back("tan", leningrad::tan<double>,
                       [](double x) { return std::tan(x); });
    funcs.emplace_back("csc", leningrad::csc<double>,
                       [](double x) { return 1.0 / std::sin(x); });
    funcs.emplace_back("sec", leningrad::sec<double>,
                       [](double x) { return 1.0 / std::cos(x); });
    funcs.emplace_back("cot", leningrad::cot<double>,
                       [](double x) { return 1.0 / std::tan(x); });
    funcs.emplace_back("atan", leningrad::atan<double>,
                       [](double x) { return std::atan(x); });
    funcs.emplace_back("sinh", leningrad::sinh<double>,
                       [](double x) { return std::sinh(x); });
    funcs.emplace_back("cosh", leningrad::cosh<double>,
                       [](double x) { return std::cosh(x); });
    funcs.emplace_back("tanh", leningrad::tanh<double>,
                       [](double x) { return std::tanh(x); });
    funcs.emplace_back("asinh", leningrad::asinh<double>,
                       [](double x) { return std::asinh(x); });
    funcs.emplace_back("erf", leningrad::erf<double>,
                       [](double x) { return std::erf(x); });
    funcs.emplace_back("erfc", leningrad::erfc<double>,
                       [](double x) { return std::erfc(x); });

    std::vector<double> points{0.1, 1, -1, 3.5, -3.5};

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
            REQUIRE(dydx == Approx(dydxTrue).margin(1e-4));
        }
    }
}

TEST_CASE("Test univariate funcs over R+", "[DiffOp]") {
    std::vector<std::tuple<std::string, std::function<ddouble(const ddouble &)>,
                           std::function<double(double)>>>
        funcs;
    funcs.emplace_back("sqrt", leningrad::sqrt<double>,
                       [](double x) { return std::sqrt(x); });
    funcs.emplace_back(
        "log", [](const ddouble &x) { return log(x); },
        [](double x) { return std::log(x); });
    funcs.emplace_back("log10", leningrad::log10<double>,
                       [](double x) { return std::log10(x); });
    funcs.emplace_back("log2", leningrad::log2<double>,
                       [](double x) { return std::log2(x); });
    funcs.emplace_back("acosh", leningrad::acosh<double>,
                       [](double x) { return std::acosh(x); });

    std::vector<double> points{1.1, 2, 3.5};

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

TEST_CASE("Test asin and acos", "[DiffOp]") {
    std::vector<double> points{-0.9, -0.5, 0, 0.5, 0.9};
    for (double p : points) {
        ddouble x(p);
        INFO("Testing acos at x=" << p);
        REQUIRE((differentiate(acos(x)).wrt(x) ==
                 Approx(numericalDifferentiate(
                     [](double x) { return std::acos(x); }, p))));
        INFO("Testing asin at x=" << p);
        REQUIRE((differentiate(asin(x)).wrt(x) ==
                 Approx(numericalDifferentiate(
                     [](double x) { return std::asin(x); }, p))));
    }
}

TEST_CASE("Test bivariate functions over R2", "[DiffOp]") {
    std::vector<std::tuple<
        std::string, std::function<ddouble(const ddouble &, const ddouble &)>,
        std::function<double(double, double)>>>
        funcs;
    funcs.emplace_back("hypot", leningrad::hypot<double>,
                       [](double a, double b) { return std::hypot(a, b); });
    funcs.emplace_back("atan2", leningrad::atan2<double>,
                       [](double a, double b) { return std::atan2(a, b); });
    funcs.emplace_back("copysign", leningrad::copysign<double>,
                       [](double a, double b) { return std::copysign(a, b); });

    std::vector<std::pair<double, double>> points{
        {5, 5}, {-5, 5}, {5, -5}, {-5, -5}};

    for (const auto &tuple : funcs) {
        std::string name = std::get<0>(tuple);
        std::function<ddouble(const ddouble &, const ddouble &)> diffFn =
            std::get<1>(tuple);
        std::function<double(double, double)> fn = std::get<2>(tuple);
        for (const auto &p : points) {
            ddouble x(p.first);
            ddouble y(p.second);
            ddouble z = diffFn(x, y);
            auto dz = differentiate(z);
            double dzdx = dz.wrt(x).value();
            double dzdy = dz.wrt(y).value();

            double dzdxNumerical = numericalDifferentiate(
                [&](double x) { return fn(x, p.second); }, p.first);
            double dzdyNumerical = numericalDifferentiate(
                [&](double y) { return fn(p.first, y); }, p.second);
            INFO("Testing dzdx of " << name << " at (x,y)=(" << p.first << ", "
                                    << p.second << ")");
            REQUIRE(dzdx == Approx(dzdxNumerical).margin(1e-4));
            INFO("Testing dzdy of " << name << " at (x,y)=(" << p.first << ", "
                                    << p.second << ")");
            REQUIRE(dzdy == Approx(dzdyNumerical).margin(1e-4));
        }
    }
}

TEST_CASE("Test pow", "[DiffOp]") {
    std::vector<double> xs{1, 2.5, 3};
    std::vector<double> ys{-1.5, -1, 0, 1, 1.5};

    std::vector<std::pair<double, double>> points;
    for (double x : xs) {
        for (double y : ys) {
            points.emplace_back(x, y);
        }
    }

    points.emplace_back(0, 1);
    points.emplace_back(0, 1.5);

    for (auto &pair : points) {
        double x_ = pair.first;
        double y_ = pair.second;
        ddouble x(x_);
        ddouble y(y_);
        ddouble z = pow(x, y);

        auto dz = differentiate(z);
        if (x != 0) {
            INFO("Test dzdx at (x,y)=(" << x_ << ", " << y_ << ")")
            double dzdx = dz.wrt(x).value();
            double dzdxNumerical = numericalDifferentiate(
                [y_](double p) { return std::pow(p, y_); }, x_);
            REQUIRE(dzdx == Approx(dzdxNumerical).margin(1e-4));
        }
        {
            INFO("Test dzdy at (x,y)=(" << x_ << ", " << y_ << ")")
            double dzdy = dz.wrt(y).value();
            double dzdyNumerical = numericalDifferentiate(
                [x_](double p) { return std::pow(x_, p); }, y_);
            REQUIRE(dzdy == Approx(dzdyNumerical).margin(1e-4));
        }
    }
}

TEST_CASE("Test log") {
    std::vector<double> xs{0.5, 2, M_E, M_PI};
    std::vector<double> ys{0.1, 1, M_PI, 5.3};

    for (double x_ : xs) {
        for (double y_ : ys) {
            ddouble x(x_);
            ddouble y(y_);
            ddouble z = log(x, y);

            auto dz = differentiate(z);
            {
                INFO("Test dzdx at (x,y)=(" << x_ << ", " << y_ << ")")
                double dzdx = dz.wrt(x).value();
                double dzdxNumerical = numericalDifferentiate(
                    [y_](double p) { return std::log(y_) / std::log(p); }, x_);
                REQUIRE(dzdx == Approx(dzdxNumerical).margin(1e-4));
            }
            {
                INFO("Test dzdy at (x,y)=(" << x_ << ", " << y_ << ")")
                double dzdy = dz.wrt(y).value();
                double dzdyNumerical = numericalDifferentiate(
                    [x_](double p) { return std::log(p) / std::log(x_); }, y_);
                REQUIRE(dzdy == Approx(dzdyNumerical).margin(1e-4));
            }
        }
    }
}
