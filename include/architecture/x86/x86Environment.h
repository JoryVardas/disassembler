#ifndef ARCHITECTURE_X86_X86ENVIRONMENT_H
#define ARCHITECTURE_X86_X86ENVIRONMENT_H

#include <bit>

struct X86Environment {
public:
        enum class X86AddressMode {
                X16,
                X32,
                X64
        };
        enum class X86ParameterMode {
                X16,
                X32,
                X64
        };
        enum class X86InstructionMode {
                LEGACY,
                X64,
                BOTH
        };

        X86AddressMode _defaultAdressMode;
        X86ParameterMode _defaultParameterMode;
        X86InstructionMode _defaultInstructionMode;
        std::endian _endianness;
private:
};

#endif