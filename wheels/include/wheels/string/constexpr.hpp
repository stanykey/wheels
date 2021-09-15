#ifndef WHEELS_STRING_CONSTEXPR_HPP
#define WHEELS_STRING_CONSTEXPR_HPP

#include <cstdint>
#include <cstddef>


namespace wheels {
    namespace string {
        std::size_t constexpr length(const char* str)
        {
            return *str? (1 + length(str + 1)) : 0;
        }

        // FNV-1a 32bit hashing algorithm.
        constexpr std::uint32_t hash(const char* str, const std::size_t count)
        {
            return ((count? hash(str, count - 1) : 2166136261u) ^ str[count]) * 16777619u;
        }

        constexpr std::uint32_t hash(const char* str)
        {
            return hash(str, length(str));
        }

        constexpr std::uint32_t operator"" _hash(const char* str, const std::size_t count)
        {
            return hash(str, count);
        }
    }
}

#endif //WHEELS_STRING_CONSTEXPR_HPP
