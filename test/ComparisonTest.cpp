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

TEST_CASE("Test min", "[Comparison]") {
    ddouble x = 3;
    SECTION("Test min with ddouble") {
        ddouble y = 4;
        ddouble z = min(x, y);
        auto dz = differentiate(z);
        REQUIRE((dz.wrt(x) == 1));
        REQUIRE((dz.wrt(y) == 0));
    }

    SECTION("Test min with larger double") {
        double y = 4;
        ddouble z = min(x, y);
        auto dz = differentiate(z);
        REQUIRE((dz.wrt(x) == 1));
        REQUIRE((dz.wrt(y) == 0));
    }

    SECTION("Test min with smaller double") {
        double y = 2;
        ddouble z = min(x, y);
        REQUIRE((differentiate(z).wrt(x) == 0));
    }
}

TEST_CASE("Test max", "[Comparison]") {
    ddouble x = 3;
    SECTION("Test max with ddouble") {
        ddouble y = 2;
        ddouble z = max(x, y);
        auto dz = differentiate(z);
        REQUIRE((dz.wrt(x) == 1));
        REQUIRE((dz.wrt(y) == 0));
    }

    SECTION("Test max with smaller double") {
        double y = 2;
        ddouble z = max(x, y);
        auto dz = differentiate(z);
        REQUIRE((dz.wrt(x) == 1));
        REQUIRE((dz.wrt(y) == 0));
    }

    SECTION("Test max with larger double") {
        double y = 4;
        ddouble z = max(x, y);
        REQUIRE((differentiate(z).wrt(x) == 0));
    }
}

