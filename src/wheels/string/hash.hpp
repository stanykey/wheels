#ifndef WHEELS_STRING_HASH_HPP
#define WHEELS_STRING_HASH_HPP

#include <cstdint>


namespace wheels::string {
    using hash_type = std::uint64_t;

    // FNV-1a 64-bit hash.
    constexpr hash_type FNV_BASIS = 14695981039346656037ull;
    constexpr hash_type FNV_PRIME = 1099511628211ull;

    constexpr std::uint32_t hash(const char* str, hash_type basis = FNV_BASIS) {
        return (*str != 0) ? hash(str + 1, (basis ^ *str) * FNV_PRIME) : basis;
    }

}  // namespace wheels::string

#endif  // WHEELS_STRING_HASH_HPP
