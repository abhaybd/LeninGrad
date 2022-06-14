#include <catch2/catch.hpp>

#include "../src/Core.h"

using namespace leningrad;

TEST_CASE("Test DiffValue Comparison", "[DiffValue][Comparison]") {
    REQUIRE((ddouble(3) == 3));
    REQUIRE_FALSE((ddouble(3) == 4));
    REQUIRE((ddouble(3) != 4));
    REQUIRE_FALSE((ddouble(3) != 3));
    REQUIRE((ddouble(3) > 2));
    REQUIRE_FALSE((ddouble(3) > 4));
    REQUIRE((ddouble(3) < 4));
    REQUIRE_FALSE((ddouble(3) < 2));
    REQUIRE((ddouble(3) <= 3));
    REQUIRE_FALSE((ddouble(3) <= 2));
    REQUIRE((ddouble(3) >= 3));
    REQUIRE_FALSE((ddouble(3) >= 4));
}
