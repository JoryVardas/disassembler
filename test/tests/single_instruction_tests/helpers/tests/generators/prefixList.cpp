#include "../../generators/prefixList.hpp"
#include <catch2/catch_test_macros.hpp>
#include <catch2/generators/catch_generators_range.hpp>

using namespace Testing::Helpers::Generators;

TEST_CASE("prefixlistGenerator", "[helper test][generator]") {
    using PrefixList_t = std::vector<Testing::Helpers::prefix_t>;
    SECTION("one prefix") {
        auto gen = generatePrefixList(LOCK_PREFIX);
        REQUIRE(gen.get().size() == 1);
        REQUIRE(gen.get() == PrefixList_t{LOCK_PREFIX});
        REQUIRE(!gen.next());
    }
    SECTION("one prefix from generator") {
        auto gen = generatePrefixList(Catch::Generators::value(LOCK_PREFIX));
        REQUIRE(gen.get().size() == 1);
        REQUIRE(gen.get() == PrefixList_t{LOCK_PREFIX});
        REQUIRE(!gen.next());
    }
    SECTION("one prefix from optional generator") {
        auto gen = generatePrefixList(
            std::optional{Catch::Generators::value(LOCK_PREFIX)});
        REQUIRE(gen.get().size() == 1);
        REQUIRE(gen.get() == PrefixList_t{LOCK_PREFIX});
        REQUIRE(!gen.next());
    }
    SECTION("one prefix with additional optional generator not set") {
        auto gen = generatePrefixList(
            LOCK_PREFIX, std::optional<Catch::Generators::GeneratorWrapper<
                             Testing::Helpers::prefix_t>>{std::nullopt});
        REQUIRE(gen.get().size() == 1);
        REQUIRE(gen.get() == PrefixList_t{LOCK_PREFIX});
        REQUIRE(!gen.next());
    }
    SECTION("three prefixes from different groups, including a REX prefix") {
        auto gen = generatePrefixList(LOCK_PREFIX, OPERAND_SIZE_OVERRIDE_PREFIX,
                                      REX_PREFIX);
        REQUIRE(gen.get() == PrefixList_t{LOCK_PREFIX,
                                          OPERAND_SIZE_OVERRIDE_PREFIX,
                                          REX_PREFIX});
        REQUIRE(gen.next());
        REQUIRE(gen.get() == PrefixList_t{OPERAND_SIZE_OVERRIDE_PREFIX,
                                          LOCK_PREFIX, REX_PREFIX});
        REQUIRE(!gen.next());
    }
    SECTION("four prefixes from two different groups") {
        auto gen = generatePrefixList(LOCK_PREFIX, SS_SEGMENT_OVERRIDE_PREFIX,
                                      ES_SEGMENT_OVERRIDE_PREFIX, REP_PREFIX);
        REQUIRE(gen.get() ==
                PrefixList_t{LOCK_PREFIX, SS_SEGMENT_OVERRIDE_PREFIX});
        REQUIRE(gen.next());
        REQUIRE(gen.get() ==
                PrefixList_t{SS_SEGMENT_OVERRIDE_PREFIX, LOCK_PREFIX});
        REQUIRE(gen.next());
        REQUIRE(gen.get() ==
                PrefixList_t{LOCK_PREFIX, ES_SEGMENT_OVERRIDE_PREFIX});
        REQUIRE(gen.next());
        REQUIRE(gen.get() ==
                PrefixList_t{ES_SEGMENT_OVERRIDE_PREFIX, LOCK_PREFIX});
        REQUIRE(gen.next());
        REQUIRE(gen.get() ==
                PrefixList_t{REP_PREFIX, SS_SEGMENT_OVERRIDE_PREFIX});
        REQUIRE(gen.next());
        REQUIRE(gen.get() ==
                PrefixList_t{SS_SEGMENT_OVERRIDE_PREFIX, REP_PREFIX});
        REQUIRE(gen.next());
        REQUIRE(gen.get() ==
                PrefixList_t{REP_PREFIX, ES_SEGMENT_OVERRIDE_PREFIX});
        REQUIRE(gen.next());
        REQUIRE(gen.get() ==
                PrefixList_t{ES_SEGMENT_OVERRIDE_PREFIX, REP_PREFIX});
        REQUIRE(!gen.next());
    }
}