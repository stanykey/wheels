#ifndef WHEELS_STRING_CONSTEXPR_HPP
#define WHEELS_STRING_CONSTEXPR_HPP

#include <cstdint>
#include <cstddef>


namespace wheels {
    namespace string {
        std::size_t constexpr length(char const* str)
        {
            return *str? (1 + length(str + 1)) : 0;
        }

        // FNV-1a 32bit hashing algorithm.
        constexpr std::uint32_t hash(char const* str, std::size_t const count)
        {
            return ((count? hash(str, count - 1) : 2166136261u) ^ str[count]) * 16777619u;
        }

        constexpr std::uint32_t hash(char const* str)
        {
            return hash(str, length(str));
        }

        constexpr std::uint32_t operator"" _hash(char const* str, std::size_t count)
        {
            return hash(str, count);
        }
    }
}

#endif //WHEELS_STRING_CONSTEXPR_HPP
