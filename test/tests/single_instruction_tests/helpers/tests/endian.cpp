#include "../endian.hpp"
#include <catch2/catch_test_macros.hpp>
#include <catch2/generators/catch_generators.hpp>
#include <catch2/generators/catch_generators_adapters.hpp>
#include <catch2/generators/catch_generators_random.hpp>

using namespace Testing::Helpers;

TEST_CASE("Endian", "[helper test]") {
    SECTION("Swap endian") {
        SECTION("1 byte") {
            uint8_t val = static_cast<uint8_t>(
                GENERATE(take(10, random(uint8_t{0x00}, uint8_t{0xFF}))));
            uint8_t val_copy = val;
            uint8_t swapped = swapEndian(val);
            REQUIRE(val == val_copy);
            REQUIRE(val == swapped);
        }
        SECTION("2 bytes") {
            uint16_t val = static_cast<uint16_t>(
                GENERATE(take(10, random(uint16_t{0x0000}, uint16_t{0xFFFF}))));
            uint16_t val_copy = val;
            uint16_t swapped = swapEndian(val);
            uint16_t swapped2 = swapEndian(swapped);
            REQUIRE(val == val_copy);
            REQUIRE(val != swapped);
            REQUIRE(swapped2 != swapped);
            REQUIRE(swapped2 == val);
        }
        SECTION("4 bytes") {
            uint32_t val = static_cast<uint32_t>(GENERATE(
                take(10, random(uint32_t{0x00000000}, uint32_t{0xFFFFFFFF}))));
            uint32_t val_copy = val;
            uint32_t swapped = swapEndian(val);
            uint32_t swapped2 = swapEndian(swapped);
            REQUIRE(val == val_copy);
            REQUIRE(val != swapped);
            REQUIRE(swapped2 != swapped);
            REQUIRE(swapped2 == val);
        }
        SECTION("8 bytes") {
            uint64_t val = static_cast<uint64_t>(
                GENERATE(take(10, random(uint64_t{0x0000000000000000},
                                         uint64_t{0xFFFFFFFFFFFFFFFF}))));
            uint64_t val_copy = val;
            uint64_t swapped = swapEndian(val);
            uint64_t swapped2 = swapEndian(swapped);
            REQUIRE(val == val_copy);
            REQUIRE(val != swapped);
            REQUIRE(swapped2 != swapped);
            REQUIRE(swapped2 == val);
        }
    }
    SECTION("toLittleEndian") {
        SECTION("1 byte") {
            uint8_t val = static_cast<uint8_t>(
                GENERATE(take(10, random(uint8_t{0x00}, uint8_t{0xFF}))));
            uint8_t val_copy = val;
            uint8_t swapped = toLittleEndian(val);
            REQUIRE(val == val_copy);
            REQUIRE(val == swapped);
        }
        SECTION("2 bytes") {
            uint16_t val = static_cast<uint16_t>(
                GENERATE(take(10, random(uint16_t{0x0000}, uint16_t{0xFFFF}))));
            uint16_t val_copy = val;
            uint16_t swapped = toLittleEndian(val);
            if (std::endian::native == std::endian::little) {
                REQUIRE(val == val_copy);
                REQUIRE(val == swapped);
            } else {
                REQUIRE(val == val_copy);
                REQUIRE(val != swapped);
            }
        }
        SECTION("4 bytes") {
            uint32_t val = static_cast<uint32_t>(GENERATE(
                take(10, random(uint32_t{0x00000000}, uint32_t{0xFFFFFFFF}))));
            uint32_t val_copy = val;
            uint32_t swapped = toLittleEndian(val);
            if (std::endian::native == std::endian::little) {
                REQUIRE(val == val_copy);
                REQUIRE(val == swapped);
            } else {
                REQUIRE(val == val_copy);
                REQUIRE(val != swapped);
            }
        }
        SECTION("8 bytes") {
            uint64_t val = static_cast<uint64_t>(
                GENERATE(take(10, random(uint64_t{0x0000000000000000},
                                         uint64_t{0xFFFFFFFFFFFFFFFF}))));
            uint64_t val_copy = val;
            uint64_t swapped = toLittleEndian(val);
            if (std::endian::native == std::endian::little) {
                REQUIRE(val == val_copy);
                REQUIRE(val == swapped);
            } else {
                REQUIRE(val == val_copy);
                REQUIRE(val != swapped);
            }
        }
    }
    SECTION("toBigEndian") {
        SECTION("1 byte") {
            uint8_t val = static_cast<uint8_t>(
                GENERATE(take(10, random(uint8_t{0x00}, uint8_t{0xFF}))));
            uint8_t val_copy = val;
            uint8_t swapped = toBigEndian(val);
            REQUIRE(val == val_copy);
            REQUIRE(val == swapped);
        }
        SECTION("2 bytes") {
            uint16_t val = static_cast<uint16_t>(
                GENERATE(take(10, random(uint16_t{0x0000}, uint16_t{0xFFFF}))));
            uint16_t val_copy = val;
            uint16_t swapped = toBigEndian(val);
            if (std::endian::native == std::endian::little) {
                REQUIRE(val == val_copy);
                REQUIRE(val != swapped);
            } else {
                REQUIRE(val == val_copy);
                REQUIRE(val == swapped);
            }
        }
        SECTION("4 bytes") {
            uint32_t val = static_cast<uint32_t>(GENERATE(
                take(10, random(uint32_t{0x00000000}, uint32_t{0xFFFFFFFF}))));
            uint32_t val_copy = val;
            uint32_t swapped = toBigEndian(val);
            if (std::endian::native == std::endian::little) {
                REQUIRE(val == val_copy);
                REQUIRE(val != swapped);
            } else {
                REQUIRE(val == val_copy);
                REQUIRE(val == swapped);
            }
        }
        SECTION("8 bytes") {
            uint64_t val = static_cast<uint64_t>(
                GENERATE(take(10, random(uint64_t{0x0000000000000000},
                                         uint64_t{0xFFFFFFFFFFFFFFFF}))));
            uint64_t val_copy = val;
            uint64_t swapped = toBigEndian(val);
            if (std::endian::native == std::endian::little) {
                REQUIRE(val == val_copy);
                REQUIRE(val != swapped);
            } else {
                REQUIRE(val == val_copy);
                REQUIRE(val == swapped);
            }
        }
    }
}