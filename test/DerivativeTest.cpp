#include <catch2/catch.hpp>

#include "../src/Core.h"

using namespace leningrad;

TEST_CASE("Test Derivative") {
    ddouble x = 3;
    ddouble y = 10;
    ddouble u = x * y;
    ddouble v = x / y;
    ddouble z = u - v;
    auto result = differentiate(z);

    REQUIRE(result.wrt(x).value() == Approx(y.value() - 1 / y.value()));
    REQUIRE(result.wrt(y).value() ==
            Approx(x.value() * (1 / (y.value() * y.value()) + 1)));
}