#include "../../generators/not_in.hpp"
#include <catch2/catch_test_macros.hpp>
#include <catch2/generators/catch_generators_range.hpp>

using namespace Testing::Helpers::Generators;

TEST_CASE("NotInGenerator", "[helper test][generator]") {
    SECTION("not_in using std::vector<int> with values 1") {
        auto gen =
            not_in(Catch::Generators::from_range(std::vector<int>{1, 2, 3, 4}),
                   std::vector<int>{1, 2, 4});
        REQUIRE(gen.get() == 3);
        REQUIRE(!gen.next());
    }
    SECTION("not_in using std::vector<int> with values 2") {
        auto gen =
            not_in(Catch::Generators::from_range(std::vector<int>{1, 2, 3, 4}),
                   std::vector<int>{1, 5, 7});
        REQUIRE(gen.get() == 2);
        REQUIRE(gen.next());
        REQUIRE(gen.get() == 3);
        REQUIRE(gen.next());
        REQUIRE(gen.get() == 4);
        REQUIRE(!gen.next());
    }
    SECTION("not_in using std::vector<int> without values 1") {
        REQUIRE_THROWS(not_in(Catch::Generators::from_range(std::vector<int>{}),
                              std::vector<int>{1, 5, 7}));
    }
    SECTION("not_in using std::vector<int> without values 2") {
        REQUIRE_NOTHROW(
            not_in(Catch::Generators::from_range(std::vector<int>{1, 2}),
                   std::vector<int>{}));

        auto gen = not_in(Catch::Generators::from_range(std::vector<int>{1, 2}),
                          std::vector<int>{});

        REQUIRE(gen.get() == 1);
        REQUIRE(gen.next());
        REQUIRE(gen.get() == 2);
        REQUIRE(!gen.next());
    }
    SECTION("not_in using from_range generator") {
        auto gen = not_in(Catch::Generators::from_range(std::vector<int>{1, 2}),
                          Catch::Generators::from_range(std::vector<int>{1}));

        REQUIRE(gen.get() == 2);
        REQUIRE(!gen.next());
    }
}
