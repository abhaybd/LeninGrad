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