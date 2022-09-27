#ifndef TEST_SINGLE_INSTRUCTION_TESTS_HELPERS_ENDIAN_HELPERS_H
#define TEST_SINGLE_INSTRUCTION_TESTS_HELPERS_ENDIAN_HELPERS_H

#include <algorithm>
#include <bit>
#include <concepts>
#include <ranges>

namespace Testing::Helpers {
namespace {
// swapEndian is modified from
// https://mklimenko.github.io/english/2018/08/22/robust-endian-swap/
template <typename T> T swapEndian(T val) {
    union U {
        T val;
        std::array<std::uint8_t, sizeof(T)> raw;
    } src /*, dst*/;

    src.val = val;
    // std::reverse_copy(src.raw.begin(), src.raw.end(), dst.raw.begin());
    std::ranges::reverse(std::ranges::begin(src.raw),
                         std::ranges::end(src.raw));
    return src.val; // dst.val;
}

template <typename T> T toBigEndian(T val) {
    if (std::endian::native == std::endian::big)
        return val;
    else {
        return swapEndian(val);
    }
}
template <typename T> T toLittleEndian(T val) {
    if (std::endian::native == std::endian::little)
        return val;
    else {
        return swapEndian(val);
    }
}
} // namespace
} // namespace Testing::Helpers

#endif