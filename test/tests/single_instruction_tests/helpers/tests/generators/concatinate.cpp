#include "../../generators/concatenate.hpp"
#include <catch2/catch_test_macros.hpp>
#include <catch2/generators/catch_generators_range.hpp>

using namespace Testing::Helpers::Generators;

TEST_CASE("concatinateGenerator", "[helper test][generator]") {
    SECTION("two from_range generators") {
        auto gen =
            concatenate(Catch::Generators::from_range(std::vector<int>{1, 2}),
                        Catch::Generators::from_range(std::vector<int>{3, 4}));
        REQUIRE(gen.get() == 1);
        REQUIRE(gen.next());
        REQUIRE(gen.get() == 2);
        REQUIRE(gen.next());
        REQUIRE(gen.get() == 3);
        REQUIRE(gen.next());
        REQUIRE(gen.get() == 4);
        REQUIRE(!gen.next());
    }
    SECTION("one from_range generator") {
        auto gen =
            concatenate(Catch::Generators::from_range(std::vector<int>{1, 2}));
        REQUIRE(gen.get() == 1);
        REQUIRE(gen.next());
        REQUIRE(gen.get() == 2);
        REQUIRE(!gen.next());
    }
    SECTION("one from_range generator and two value generators") {
        auto gen = concatenate(
            Catch::Generators::from_range(std::vector<int>{1, 2}),
            Catch::Generators::value(1), Catch::Generators::value(2));
        REQUIRE(gen.get() == 1);
        REQUIRE(gen.next());
        REQUIRE(gen.get() == 2);
        REQUIRE(gen.next());
        REQUIRE(gen.get() == 1);
        REQUIRE(gen.next());
        REQUIRE(gen.get() == 2);
        REQUIRE(!gen.next());
    }
}