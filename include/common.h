#ifndef COMMON_H
#define COMMON_H

#define RAW_MACRO_CONCAT(x, y) x##y
#define MACRO_CONCAT(x, y) RAW_MACRO_CONCAT(x, y)
#define PADDING(size) char MACRO_CONCAT(_padding_, __COUNTER__)[size]

template <typename Container, typename Predicate>
constexpr auto erase_if(Container& container, Predicate predicate) {
    return container.erase(
        std::remove_if(std::begin(container), std::end(container), predicate),
        std::cend(container));
}

#endif