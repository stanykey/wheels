#ifndef WHEELS_STRING_CONSTEXPR_HPP
#define WHEELS_STRING_CONSTEXPR_HPP

#include <cstddef>
#include <cstdint>


namespace wheels::string {
    std::size_t constexpr length(const char* str) {
        return *str != 0 ? (1 + length(str + 1)) : 0;
    }

}  // namespace wheels::string

#endif  // WHEELS_STRING_CONSTEXPR_HPP
