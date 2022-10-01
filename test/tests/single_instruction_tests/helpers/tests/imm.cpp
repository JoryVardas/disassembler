#include "../imm.hpp"
#include "../endian.hpp"
#include <catch2/catch_test_macros.hpp>
#include <catch2/generators/catch_generators.hpp>
#include <catch2/generators/catch_generators_adapters.hpp>
#include <catch2/generators/catch_generators_random.hpp>
#include <fmt/format.h>

using namespace Testing::Helpers;

TEST_CASE("IMM", "[helper test]") {
    SECTION("Assumption: bitwise operations") {
        SECTION("1 byte") {
            uint8_t val8 = toBigEndian(GENERATE(uint8_t{0xEA}));
            REQUIRE(static_cast<uint8_t>(val8) == uint8_t{0xEA});
        }
        SECTION("2 bytes") {
            uint16_t val16 = GENERATE(uint16_t{0xBEEF});
            REQUIRE(static_cast<uint8_t>((val16 & 0xFF00) >> 8) ==
                    uint8_t{0xBE});
            REQUIRE(static_cast<uint8_t>((val16 & 0x00FF)) == uint8_t{0xEF});
        }
        SECTION("4 bytes") {
            uint32_t val32 = GENERATE(uint32_t{0xDEADBEEF});
            REQUIRE(static_cast<uint8_t>((val32 & 0xFF000000) >> 24) ==
                    uint8_t{0xDE});
            REQUIRE(static_cast<uint8_t>((val32 & 0x00FF0000) >> 16) ==
                    uint8_t{0xAD});
            REQUIRE(static_cast<uint8_t>((val32 & 0x0000FF00) >> 8) ==
                    uint8_t{0xBE});
            REQUIRE(static_cast<uint8_t>((val32 & 0x000000FF)) ==
                    uint8_t{0xEF});
        }
        SECTION("8 bytes") {
            uint64_t val64 = GENERATE(uint64_t{0xABCDEFCDABCDEFCD});
            REQUIRE(static_cast<uint8_t>((val64 & 0xFF00000000000000) >> 56) ==
                    uint8_t{0xAB});
            REQUIRE(static_cast<uint8_t>((val64 & 0x00FF000000000000) >> 48) ==
                    uint8_t{0xCD});
            REQUIRE(static_cast<uint8_t>((val64 & 0x0000FF0000000000) >> 40) ==
                    uint8_t{0xEF});
            REQUIRE(static_cast<uint8_t>((val64 & 0x000000FF00000000) >> 32) ==
                    uint8_t{0xCD});
            REQUIRE(static_cast<uint8_t>((val64 & 0x00000000FF000000) >> 24) ==
                    uint8_t{0xAB});
            REQUIRE(static_cast<uint8_t>((val64 & 0x0000000000FF0000) >> 16) ==
                    uint8_t{0xCD});
            REQUIRE(static_cast<uint8_t>((val64 & 0x000000000000FF00) >> 8) ==
                    uint8_t{0xEF});
            REQUIRE(static_cast<uint8_t>((val64 & 0x00000000000000FF)) ==
                    uint8_t{0xCD});
        }
    }
    SECTION("IMM8") {
        uint8_t imm_val = static_cast<uint8_t>(
            GENERATE(take(10, random(uint8_t{0x00}, uint8_t{0xFF}))));
        INFO(fmt::format("IMM Value: {}", imm_val));
        IMMParameter imm{imm_val};
        REQUIRE(imm.toString({}) == fmt::format("{:#x}", toBigEndian(imm_val)));
        REQUIRE(imm.toByteVector(std::endian::little)[0] == std::byte{imm_val});
        REQUIRE(imm.toByteVector(std::endian::big)[0] == std::byte{imm_val});
    }
    SECTION("IMM16") {
        uint16_t imm_val = static_cast<uint16_t>(
            GENERATE(take(10, random(uint16_t{0x0000}, uint16_t{0xFFFF}))));
        INFO(fmt::format("IMM Value: {}", imm_val));
        uint16_t imm_val_swapped = swapEndian(imm_val);
        IMMParameter imm{imm_val};
        REQUIRE(imm.toString({}) == fmt::format("{:#x}", imm_val));
        REQUIRE(imm.toByteVector(std::endian::big)[0] ==
                std::byte{static_cast<uint8_t>((imm_val & 0xFF00) >> 8)});
        REQUIRE(imm.toByteVector(std::endian::big)[1] ==
                std::byte{static_cast<uint8_t>((imm_val & 0x00FF))});
        REQUIRE(
            imm.toByteVector(std::endian::little)[0] ==
            std::byte{static_cast<uint8_t>((imm_val_swapped & 0xFF00) >> 8)});
        REQUIRE(imm.toByteVector(std::endian::little)[1] ==
                std::byte{static_cast<uint8_t>((imm_val_swapped & 0x00FF))});
    }
    SECTION("IMM32") {
        uint32_t imm_val = static_cast<uint32_t>(GENERATE(
            take(10, random(uint32_t{0x00000000}, uint32_t{0xFFFFFFFF}))));
        INFO(fmt::format("IMM Value: {}", imm_val));
        uint32_t imm_val_swapped = swapEndian(imm_val);
        IMMParameter imm{imm_val};
        REQUIRE(imm.toString({}) == fmt::format("{:#x}", imm_val));
        REQUIRE(imm.toByteVector(std::endian::big)[0] ==
                std::byte{static_cast<uint8_t>((imm_val & 0xFF000000) >> 24)});
        REQUIRE(imm.toByteVector(std::endian::big)[1] ==
                std::byte{static_cast<uint8_t>((imm_val & 0x00FF0000) >> 16)});
        REQUIRE(imm.toByteVector(std::endian::big)[2] ==
                std::byte{static_cast<uint8_t>((imm_val & 0x0000FF00) >> 8)});
        REQUIRE(imm.toByteVector(std::endian::big)[3] ==
                std::byte{static_cast<uint8_t>((imm_val & 0x000000FF))});
        REQUIRE(imm.toByteVector(std::endian::little)[0] ==
                std::byte{static_cast<uint8_t>((imm_val_swapped & 0xFF000000) >>
                                               24)});
        REQUIRE(imm.toByteVector(std::endian::little)[1] ==
                std::byte{static_cast<uint8_t>((imm_val_swapped & 0x00FF0000) >>
                                               16)});
        REQUIRE(imm.toByteVector(std::endian::little)[2] ==
                std::byte{
                    static_cast<uint8_t>((imm_val_swapped & 0x0000FF00) >> 8)});
        REQUIRE(
            imm.toByteVector(std::endian::little)[3] ==
            std::byte{static_cast<uint8_t>((imm_val_swapped & 0x000000FF))});
    }
    SECTION("IMM64") {
        uint64_t imm_val = static_cast<uint64_t>(
            GENERATE(take(10, random(uint64_t{0x0000000000000000},
                                     uint64_t{0xFFFFFFFFFFFFFFFF}))));
        INFO(fmt::format("IMM Value: {}", imm_val));
        uint64_t imm_val_swapped = swapEndian(imm_val);
        IMMParameter imm{imm_val};
        REQUIRE(imm.toString({}) == fmt::format("{:#x}", imm_val));
        REQUIRE(imm.toByteVector(std::endian::big)[0] ==
                std::byte{static_cast<uint8_t>((imm_val & 0xFF00000000000000) >>
                                               56)});
        REQUIRE(imm.toByteVector(std::endian::big)[1] ==
                std::byte{static_cast<uint8_t>((imm_val & 0x00FF000000000000) >>
                                               48)});
        REQUIRE(imm.toByteVector(std::endian::big)[2] ==
                std::byte{static_cast<uint8_t>((imm_val & 0x0000FF0000000000) >>
                                               40)});
        REQUIRE(imm.toByteVector(std::endian::big)[3] ==
                std::byte{static_cast<uint8_t>((imm_val & 0x000000FF00000000) >>
                                               32)});
        REQUIRE(imm.toByteVector(std::endian::big)[4] ==
                std::byte{static_cast<uint8_t>((imm_val & 0x00000000FF000000) >>
                                               24)});
        REQUIRE(imm.toByteVector(std::endian::big)[5] ==
                std::byte{static_cast<uint8_t>((imm_val & 0x0000000000FF0000) >>
                                               16)});
        REQUIRE(imm.toByteVector(std::endian::big)[6] ==
                std::byte{
                    static_cast<uint8_t>((imm_val & 0x000000000000FF00) >> 8)});
        REQUIRE(
            imm.toByteVector(std::endian::big)[7] ==
            std::byte{static_cast<uint8_t>((imm_val & 0x00000000000000FF))});
        REQUIRE(imm.toByteVector(std::endian::little)[0] ==
                std::byte{static_cast<uint8_t>(
                    (imm_val_swapped & 0xFF00000000000000) >> 56)});
        REQUIRE(imm.toByteVector(std::endian::little)[1] ==
                std::byte{static_cast<uint8_t>(
                    (imm_val_swapped & 0x00FF000000000000) >> 48)});
        REQUIRE(imm.toByteVector(std::endian::little)[2] ==
                std::byte{static_cast<uint8_t>(
                    (imm_val_swapped & 0x0000FF0000000000) >> 40)});
        REQUIRE(imm.toByteVector(std::endian::little)[3] ==
                std::byte{static_cast<uint8_t>(
                    (imm_val_swapped & 0x000000FF00000000) >> 32)});
        REQUIRE(imm.toByteVector(std::endian::little)[4] ==
                std::byte{static_cast<uint8_t>(
                    (imm_val_swapped & 0x00000000FF000000) >> 24)});
        REQUIRE(imm.toByteVector(std::endian::little)[5] ==
                std::byte{static_cast<uint8_t>(
                    (imm_val_swapped & 0x0000000000FF0000) >> 16)});
        REQUIRE(imm.toByteVector(std::endian::little)[6] ==
                std::byte{static_cast<uint8_t>(
                    (imm_val_swapped & 0x000000000000FF00) >> 8)});
        REQUIRE(imm.toByteVector(std::endian::little)[7] ==
                std::byte{static_cast<uint8_t>(
                    (imm_val_swapped & 0x00000000000000FF))});
    }
}