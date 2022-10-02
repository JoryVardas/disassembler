#include "../../generators/x86Environment.hpp"
#include <catch2/catch_test_macros.hpp>

using namespace Testing::Helpers::Generators;

TEST_CASE("X86EnvironmentGenerator",
          "[helper test][x86environment][generator]") {
    SECTION("legacy") {
        auto gen =
            generateX86Environment(X86Environment::X86InstructionMode::LEGACY);

        const X86Environment& env0000 = gen.get();
        REQUIRE(env0000._endianness == std::endian::little);
        REQUIRE(env0000._defaultAdressMode ==
                X86Environment::X86AddressMode::X16);
        REQUIRE(env0000._defaultParameterMode ==
                X86Environment::X86ParameterMode::X16);
        REQUIRE(env0000._defaultInstructionMode ==
                X86Environment::X86InstructionMode::LEGACY);

        REQUIRE(gen.next());

        const X86Environment& env0001 = gen.get();
        REQUIRE(env0001._endianness == std::endian::big);
        REQUIRE(env0001._defaultAdressMode ==
                X86Environment::X86AddressMode::X16);
        REQUIRE(env0001._defaultParameterMode ==
                X86Environment::X86ParameterMode::X16);
        REQUIRE(env0001._defaultInstructionMode ==
                X86Environment::X86InstructionMode::LEGACY);

        REQUIRE(gen.next());

        const X86Environment& env0010 = gen.get();
        REQUIRE(env0010._endianness == std::endian::little);
        REQUIRE(env0010._defaultAdressMode ==
                X86Environment::X86AddressMode::X32);
        REQUIRE(env0010._defaultParameterMode ==
                X86Environment::X86ParameterMode::X16);
        REQUIRE(env0010._defaultInstructionMode ==
                X86Environment::X86InstructionMode::LEGACY);

        REQUIRE(gen.next());

        const X86Environment& env0011 = gen.get();
        REQUIRE(env0011._endianness == std::endian::big);
        REQUIRE(env0011._defaultAdressMode ==
                X86Environment::X86AddressMode::X32);
        REQUIRE(env0011._defaultParameterMode ==
                X86Environment::X86ParameterMode::X16);
        REQUIRE(env0011._defaultInstructionMode ==
                X86Environment::X86InstructionMode::LEGACY);

        REQUIRE(gen.next());

        const X86Environment& env0100 = gen.get();
        REQUIRE(env0100._endianness == std::endian::little);
        REQUIRE(env0100._defaultAdressMode ==
                X86Environment::X86AddressMode::X16);
        REQUIRE(env0100._defaultParameterMode ==
                X86Environment::X86ParameterMode::X32);
        REQUIRE(env0100._defaultInstructionMode ==
                X86Environment::X86InstructionMode::LEGACY);

        REQUIRE(gen.next());

        const X86Environment& env0101 = gen.get();
        REQUIRE(env0101._endianness == std::endian::big);
        REQUIRE(env0101._defaultAdressMode ==
                X86Environment::X86AddressMode::X16);
        REQUIRE(env0101._defaultParameterMode ==
                X86Environment::X86ParameterMode::X32);
        REQUIRE(env0101._defaultInstructionMode ==
                X86Environment::X86InstructionMode::LEGACY);

        REQUIRE(gen.next());

        const X86Environment& env0110 = gen.get();
        REQUIRE(env0110._endianness == std::endian::little);
        REQUIRE(env0110._defaultAdressMode ==
                X86Environment::X86AddressMode::X32);
        REQUIRE(env0110._defaultParameterMode ==
                X86Environment::X86ParameterMode::X32);
        REQUIRE(env0110._defaultInstructionMode ==
                X86Environment::X86InstructionMode::LEGACY);

        REQUIRE(gen.next());

        const X86Environment& env0111 = gen.get();
        REQUIRE(env0111._endianness == std::endian::big);
        REQUIRE(env0111._defaultAdressMode ==
                X86Environment::X86AddressMode::X32);
        REQUIRE(env0111._defaultParameterMode ==
                X86Environment::X86ParameterMode::X32);
        REQUIRE(env0111._defaultInstructionMode ==
                X86Environment::X86InstructionMode::LEGACY);

        REQUIRE(!gen.next());
    }

    SECTION("x64") {
        auto gen =
            generateX86Environment(X86Environment::X86InstructionMode::X64);

        const X86Environment& env1000 = gen.get();
        REQUIRE(env1000._endianness == std::endian::little);
        REQUIRE(env1000._defaultAdressMode ==
                X86Environment::X86AddressMode::X32);
        REQUIRE(env1000._defaultParameterMode ==
                X86Environment::X86ParameterMode::X32);
        REQUIRE(env1000._defaultInstructionMode ==
                X86Environment::X86InstructionMode::X64);

        REQUIRE(gen.next());

        const X86Environment& env1001 = gen.get();
        REQUIRE(env1001._endianness == std::endian::big);
        REQUIRE(env1001._defaultAdressMode ==
                X86Environment::X86AddressMode::X32);
        REQUIRE(env1001._defaultParameterMode ==
                X86Environment::X86ParameterMode::X32);
        REQUIRE(env1001._defaultInstructionMode ==
                X86Environment::X86InstructionMode::X64);

        REQUIRE(gen.next());

        const X86Environment& env1010 = gen.get();
        REQUIRE(env1010._endianness == std::endian::little);
        REQUIRE(env1010._defaultAdressMode ==
                X86Environment::X86AddressMode::X64);
        REQUIRE(env1010._defaultParameterMode ==
                X86Environment::X86ParameterMode::X32);
        REQUIRE(env1010._defaultInstructionMode ==
                X86Environment::X86InstructionMode::X64);

        REQUIRE(gen.next());

        const X86Environment& env1011 = gen.get();
        REQUIRE(env1011._endianness == std::endian::big);
        REQUIRE(env1011._defaultAdressMode ==
                X86Environment::X86AddressMode::X64);
        REQUIRE(env1011._defaultParameterMode ==
                X86Environment::X86ParameterMode::X32);
        REQUIRE(env1011._defaultInstructionMode ==
                X86Environment::X86InstructionMode::X64);

        REQUIRE(gen.next());

        const X86Environment& env1100 = gen.get();
        REQUIRE(env1100._endianness == std::endian::little);
        REQUIRE(env1100._defaultAdressMode ==
                X86Environment::X86AddressMode::X32);
        REQUIRE(env1100._defaultParameterMode ==
                X86Environment::X86ParameterMode::X64);
        REQUIRE(env1100._defaultInstructionMode ==
                X86Environment::X86InstructionMode::X64);

        REQUIRE(gen.next());

        const X86Environment& env1101 = gen.get();
        REQUIRE(env1101._endianness == std::endian::big);
        REQUIRE(env1101._defaultAdressMode ==
                X86Environment::X86AddressMode::X32);
        REQUIRE(env1101._defaultParameterMode ==
                X86Environment::X86ParameterMode::X64);
        REQUIRE(env1101._defaultInstructionMode ==
                X86Environment::X86InstructionMode::X64);

        REQUIRE(gen.next());

        const X86Environment& env1110 = gen.get();
        REQUIRE(env1110._endianness == std::endian::little);
        REQUIRE(env1110._defaultAdressMode ==
                X86Environment::X86AddressMode::X64);
        REQUIRE(env1110._defaultParameterMode ==
                X86Environment::X86ParameterMode::X64);
        REQUIRE(env1110._defaultInstructionMode ==
                X86Environment::X86InstructionMode::X64);

        REQUIRE(gen.next());

        const X86Environment& env1111 = gen.get();
        REQUIRE(env1111._endianness == std::endian::big);
        REQUIRE(env1111._defaultAdressMode ==
                X86Environment::X86AddressMode::X64);
        REQUIRE(env1111._defaultParameterMode ==
                X86Environment::X86ParameterMode::X64);
        REQUIRE(env1111._defaultInstructionMode ==
                X86Environment::X86InstructionMode::X64);

        REQUIRE(!gen.next());
    }

    SECTION("both") {
        auto gen =
            generateX86Environment(X86Environment::X86InstructionMode::BOTH);

        const X86Environment& env0000 = gen.get();
        REQUIRE(env0000._endianness == std::endian::little);
        REQUIRE(env0000._defaultAdressMode ==
                X86Environment::X86AddressMode::X16);
        REQUIRE(env0000._defaultParameterMode ==
                X86Environment::X86ParameterMode::X16);
        REQUIRE(env0000._defaultInstructionMode ==
                X86Environment::X86InstructionMode::LEGACY);

        REQUIRE(gen.next());

        const X86Environment& env0001 = gen.get();
        REQUIRE(env0001._endianness == std::endian::big);
        REQUIRE(env0001._defaultAdressMode ==
                X86Environment::X86AddressMode::X16);
        REQUIRE(env0001._defaultParameterMode ==
                X86Environment::X86ParameterMode::X16);
        REQUIRE(env0001._defaultInstructionMode ==
                X86Environment::X86InstructionMode::LEGACY);

        REQUIRE(gen.next());

        const X86Environment& env0010 = gen.get();
        REQUIRE(env0010._endianness == std::endian::little);
        REQUIRE(env0010._defaultAdressMode ==
                X86Environment::X86AddressMode::X32);
        REQUIRE(env0010._defaultParameterMode ==
                X86Environment::X86ParameterMode::X16);
        REQUIRE(env0010._defaultInstructionMode ==
                X86Environment::X86InstructionMode::LEGACY);

        REQUIRE(gen.next());

        const X86Environment& env0011 = gen.get();
        REQUIRE(env0011._endianness == std::endian::big);
        REQUIRE(env0011._defaultAdressMode ==
                X86Environment::X86AddressMode::X32);
        REQUIRE(env0011._defaultParameterMode ==
                X86Environment::X86ParameterMode::X16);
        REQUIRE(env0011._defaultInstructionMode ==
                X86Environment::X86InstructionMode::LEGACY);

        REQUIRE(gen.next());

        const X86Environment& env0100 = gen.get();
        REQUIRE(env0100._endianness == std::endian::little);
        REQUIRE(env0100._defaultAdressMode ==
                X86Environment::X86AddressMode::X16);
        REQUIRE(env0100._defaultParameterMode ==
                X86Environment::X86ParameterMode::X32);
        REQUIRE(env0100._defaultInstructionMode ==
                X86Environment::X86InstructionMode::LEGACY);

        REQUIRE(gen.next());

        const X86Environment& env0101 = gen.get();
        REQUIRE(env0101._endianness == std::endian::big);
        REQUIRE(env0101._defaultAdressMode ==
                X86Environment::X86AddressMode::X16);
        REQUIRE(env0101._defaultParameterMode ==
                X86Environment::X86ParameterMode::X32);
        REQUIRE(env0101._defaultInstructionMode ==
                X86Environment::X86InstructionMode::LEGACY);

        REQUIRE(gen.next());

        const X86Environment& env0110 = gen.get();
        REQUIRE(env0110._endianness == std::endian::little);
        REQUIRE(env0110._defaultAdressMode ==
                X86Environment::X86AddressMode::X32);
        REQUIRE(env0110._defaultParameterMode ==
                X86Environment::X86ParameterMode::X32);
        REQUIRE(env0110._defaultInstructionMode ==
                X86Environment::X86InstructionMode::LEGACY);

        REQUIRE(gen.next());

        const X86Environment& env0111 = gen.get();
        REQUIRE(env0111._endianness == std::endian::big);
        REQUIRE(env0111._defaultAdressMode ==
                X86Environment::X86AddressMode::X32);
        REQUIRE(env0111._defaultParameterMode ==
                X86Environment::X86ParameterMode::X32);
        REQUIRE(env0111._defaultInstructionMode ==
                X86Environment::X86InstructionMode::LEGACY);

        REQUIRE(gen.next());

        const X86Environment& env1000 = gen.get();
        REQUIRE(env1000._endianness == std::endian::little);
        REQUIRE(env1000._defaultAdressMode ==
                X86Environment::X86AddressMode::X32);
        REQUIRE(env1000._defaultParameterMode ==
                X86Environment::X86ParameterMode::X32);
        REQUIRE(env1000._defaultInstructionMode ==
                X86Environment::X86InstructionMode::X64);

        REQUIRE(gen.next());

        const X86Environment& env1001 = gen.get();
        REQUIRE(env1001._endianness == std::endian::big);
        REQUIRE(env1001._defaultAdressMode ==
                X86Environment::X86AddressMode::X32);
        REQUIRE(env1001._defaultParameterMode ==
                X86Environment::X86ParameterMode::X32);
        REQUIRE(env1001._defaultInstructionMode ==
                X86Environment::X86InstructionMode::X64);

        REQUIRE(gen.next());

        const X86Environment& env1010 = gen.get();
        REQUIRE(env1010._endianness == std::endian::little);
        REQUIRE(env1010._defaultAdressMode ==
                X86Environment::X86AddressMode::X64);
        REQUIRE(env1010._defaultParameterMode ==
                X86Environment::X86ParameterMode::X32);
        REQUIRE(env1010._defaultInstructionMode ==
                X86Environment::X86InstructionMode::X64);

        REQUIRE(gen.next());

        const X86Environment& env1011 = gen.get();
        REQUIRE(env1011._endianness == std::endian::big);
        REQUIRE(env1011._defaultAdressMode ==
                X86Environment::X86AddressMode::X64);
        REQUIRE(env1011._defaultParameterMode ==
                X86Environment::X86ParameterMode::X32);
        REQUIRE(env1011._defaultInstructionMode ==
                X86Environment::X86InstructionMode::X64);

        REQUIRE(gen.next());

        const X86Environment& env1100 = gen.get();
        REQUIRE(env1100._endianness == std::endian::little);
        REQUIRE(env1100._defaultAdressMode ==
                X86Environment::X86AddressMode::X32);
        REQUIRE(env1100._defaultParameterMode ==
                X86Environment::X86ParameterMode::X64);
        REQUIRE(env1100._defaultInstructionMode ==
                X86Environment::X86InstructionMode::X64);

        REQUIRE(gen.next());

        const X86Environment& env1101 = gen.get();
        REQUIRE(env1101._endianness == std::endian::big);
        REQUIRE(env1101._defaultAdressMode ==
                X86Environment::X86AddressMode::X32);
        REQUIRE(env1101._defaultParameterMode ==
                X86Environment::X86ParameterMode::X64);
        REQUIRE(env1101._defaultInstructionMode ==
                X86Environment::X86InstructionMode::X64);

        REQUIRE(gen.next());

        const X86Environment& env1110 = gen.get();
        REQUIRE(env1110._endianness == std::endian::little);
        REQUIRE(env1110._defaultAdressMode ==
                X86Environment::X86AddressMode::X64);
        REQUIRE(env1110._defaultParameterMode ==
                X86Environment::X86ParameterMode::X64);
        REQUIRE(env1110._defaultInstructionMode ==
                X86Environment::X86InstructionMode::X64);

        REQUIRE(gen.next());

        const X86Environment& env1111 = gen.get();
        REQUIRE(env1111._endianness == std::endian::big);
        REQUIRE(env1111._defaultAdressMode ==
                X86Environment::X86AddressMode::X64);
        REQUIRE(env1111._defaultParameterMode ==
                X86Environment::X86ParameterMode::X64);
        REQUIRE(env1111._defaultInstructionMode ==
                X86Environment::X86InstructionMode::X64);
        
        REQUIRE(!gen.next());
    }
}
