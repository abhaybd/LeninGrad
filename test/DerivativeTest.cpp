#include <catch2/catch.hpp>

#include "../src/Core.h"

using namespace leningrad;

TEST_CASE("Test Derivative", "[Derivative]") {
    ddouble x = 3;
    ddouble y = 10;
    ddouble u = x * y;
    ddouble v = x / y;
    ddouble z = u - v;
    auto result = differentiate(z);

    REQUIRE(result.wrt(x).value() == Approx(y.value() - 1 / y.value()));
    REQUIRE(result.wrt(y).value() ==
            Approx(x.value() * (1 / (y.value() * y.value()) + 1)));

    REQUIRE(differentiate(y).wrt(x).value() == 0);
}

TEST_CASE("Test Higher Order Derivative", "[Derivative]") {
    SECTION("Exp") {
        ddouble x = 3.5;
        ddouble y = exp(x);
        REQUIRE(differentiate(y, x, 4).value() == Approx(y.value()));
        REQUIRE(differentiate(y, x, 2).value() ==
                Approx(differentiate(y, {x, x}).value()));
    }

    SECTION("Polynomial") {
        ddouble x = 0.3;
        ddouble y = -1.5;
        ddouble z = square(x) * square(y);

        REQUIRE(differentiate(z, x, 2).value() ==
                Approx(2 * square(y).value()));
        REQUIRE(differentiate(z, y, 2).value() ==
                Approx(2 * square(x).value()));
    }

    SECTION("Trig") {
        ddouble x = 1.46;
        ddouble y = sin(x);
        REQUIRE(differentiate(y, x, 1).value() == Approx(cos(x).value()));
        REQUIRE(differentiate(y, x, 2).value() == Approx(-y.value()));
        REQUIRE(differentiate(y, x, 3).value() == Approx(-cos(x).value()));
        REQUIRE(differentiate(y, x, 4).value() == Approx(y.value()));
    }
}

TEST_CASE("Test Cross Derivative", "[Derivative]") {

    SECTION("Simple Polynomial") {
        ddouble x = 0.1;
        ddouble y = 10;
        ddouble z = 0.5;
        ddouble a = x * y * z * z;

        double dadxyz = 2 * z.value();
        REQUIRE(differentiate(a, {x, y, z}).value() == Approx(dadxyz));
    }

    SECTION("Exp") {
        ddouble x = 3.0;
        ddouble y = 0.1;
        ddouble z = M_PI;
        ddouble a = exp(x * y * z);
        double dadxyz =
            (exp(x * y * z) * (square(x * y * z) + 3 * x * y * z + 1)).value();
        REQUIRE(differentiate(a, {x, y, z}).value() == Approx(dadxyz));
    }

    SECTION("Polynomial") {
        ddouble x = 0.1;
        ddouble y = 10;
        ddouble z = 2;
        ddouble a = square(x * y * z);

        ddouble b = (x * y * z) * (x * y * z);

        double dadxyz = (8 * x * y * z).value();
        auto vars = {x, y, z};
        auto diff = differentiate(a, vars);
        double dadxyzCalc = diff.value();
        double dbdxyzCalc = differentiate(b, {x, y, z}).value();
        REQUIRE(dadxyzCalc == Approx(dadxyz));
        REQUIRE(dbdxyzCalc == Approx(dadxyz));
    }
}
