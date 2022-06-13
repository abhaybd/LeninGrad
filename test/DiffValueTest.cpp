#define CATCH_CONFIG_MAIN
#define CATCH_CONFIG_ENABLE_BENCHMARKING
#include <catch2/catch.hpp>

#include "../src/Core.h"

using namespace leningrad;

TEST_CASE("Test DiffValue Addition", "[DiffValue][DiffOp]") {
    ddouble a = 4;
    ddouble b = 3;
    ddouble c = a + b;
    REQUIRE((a + b).value() == 7);
    REQUIRE((a + 3.).value() == 7);
    REQUIRE((3. + a).value() == 7);
    REQUIRE((4. + b).value() == 7);
    REQUIRE((b + 4.).value() == 7);
}

TEST_CASE("DiffValue Arithmetic Benchmark", "[DiffValue][Benchmark]") {
    ddouble a = 10;
    ddouble b = 2;
    ddouble c = 42.0;
    ddouble d = -3;
    BENCHMARK("Arithmetic") {
        ddouble Z = 1;
        for (int i = 0; i < 100; i++) {
            ddouble u = a * b / c;
            ddouble v = (a + c) / (d - a);
            ddouble w = 1. - (a - b) * a / c;
            ddouble z = u / (1. - v) + w;
            Z += z;
        }
        return Z;
    };
}
