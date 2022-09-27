#include "../../generators/resettable.hpp"
#include <catch2/catch_test_macros.hpp>
#include <catch2/generators/catch_generators.hpp>

using namespace Testing::Helpers::Generators;

TEST_CASE("ResettableGenerator", "[helper test][generator]") {
    SECTION("one value") {
        auto gen = ResettableGenerator(Catch::Generators::value(1));
        REQUIRE(gen.get() == 1);
        REQUIRE(!gen.next());
        gen.reset();
        REQUIRE(gen.get() == 1);
        REQUIRE(!gen.next());
        gen.reset();
        REQUIRE(gen.get() == 1);
        REQUIRE(!gen.next());
        gen.reset();
        REQUIRE(gen.get() == 1);
        REQUIRE(!gen.next());
    }
    SECTION("three values") {
        auto gen = ResettableGenerator(Catch::Generators::values({1, 3, 4}));
        REQUIRE(gen.get() == 1);
        REQUIRE(gen.next());
        REQUIRE(gen.get() == 3);
        REQUIRE(gen.next());
        REQUIRE(gen.get() == 4);
        REQUIRE(!gen.next());
        gen.reset();
        REQUIRE(gen.get() == 1);
        REQUIRE(gen.next());
        REQUIRE(gen.get() == 3);
        REQUIRE(gen.next());
        REQUIRE(gen.get() == 4);
        REQUIRE(!gen.next());
    }
}