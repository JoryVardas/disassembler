#include <architecture\x86\x86Modrm.h>

/*
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
*/