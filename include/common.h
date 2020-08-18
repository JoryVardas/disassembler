#ifndef COMMON_H
#define COMMON_H

#define MACRO_CONCAT(x, y) x##y
#define PADDING(size) char MACRO_CONCAT(_padding_, __COUNTER__)[size]

#endif