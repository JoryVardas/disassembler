#ifndef COMMON_H
#define COMMON_H

#include <algorithm>

template <typename Container, typename Predicate>
constexpr auto erase_if(Container& container, Predicate predicate) {
    return container.erase(
        std::remove_if(std::begin(container), std::end(container), predicate),
        std::cend(container));
}

#endif