#ifndef ARCHITECTURE_X86_X86MODRM_H
#define ARCHITECTURE_X86_X86MODRM_H

#include <cstddef>
#include <stdint.h>
#include "x86Environment.h"

using modrm_t = std::byte;
using sib_t = std::byte;

#pragma warning(push)
#pragma warning(disable : 4514)

/*
constexpr std::byte getModrmMod(const modrm_t& modrm);
constexpr std::byte getModrmRM(const modrm_t& modrm);
constexpr std::byte getModrmReg(const modrm_t& modrm);

constexpr std::byte getSibScale(const sib_t& sib);
constexpr std::byte getSibIndex(const sib_t& sib);
constexpr std::byte getSibBase(const sib_t& sib);
*/

constexpr std::byte getModrmMod(const modrm_t& modrm) {
    return (modrm & std::byte(0b11000000)) >> 6;
}
constexpr std::byte getModrmRM(const modrm_t& modrm) {
    return (modrm & std::byte(0b00000111));
}
constexpr std::byte getModrmReg(const modrm_t& modrm) {
    return (modrm & std::byte(0b00111000)) >> 3;
}

constexpr std::byte getSibScale(const sib_t& sib){
    return (sib & std::byte(0b11000000)) >> 6;
}
constexpr std::byte getSibIndex(const sib_t& sib){
    return (sib & std::byte(0b00111000)) >> 3;
}
constexpr std::byte getSibBase(const sib_t& sib){
    return (sib & std::byte(0b00000111));
}

constexpr uint8_t getDisplacementSizeRequiredByModrm(modrm_t modrm, sib_t sib, X86Environment::X86AddressMode addressMode){
    switch (addressMode){
        case X86Environment::X86AddressMode::X16:
            switch (static_cast<uint8_t>(getModrmMod(modrm))){
                case 0:
                    return getModrmRM(modrm) == std::byte(6) ? uint8_t(16) : uint8_t(0);
                case 1:
                    return uint8_t(8);
                case 2:
                    return uint8_t(16);
                default:
                    return uint8_t(0);
            }
            break;
        case X86Environment::X86AddressMode::X64:
        case X86Environment::X86AddressMode::X32:
            switch (static_cast<uint8_t>(getModrmMod(modrm))){
                case 0:
                    if (getModrmRM(modrm) == std::byte(4) && getSibBase(sib) == std::byte(5)){
                        return uint8_t(32);
                    }
                    return getModrmRM(modrm) == std::byte(5) ? uint8_t(32) : uint8_t(0);
                case 1:
                    return uint8_t(8);
                case 2:
                    return uint8_t(32);
                default:
                    return uint8_t(0);
            }
            break;
    }
    return 0;
}

#pragma warning(pop)
#endif