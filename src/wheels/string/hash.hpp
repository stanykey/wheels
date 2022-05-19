#ifndef WHEELS_STRING_HASH_HPP
#define WHEELS_STRING_HASH_HPP

#include <cstdint>


namespace wheels::string {
    using hash_type = std::uint64_t;

    //
    // FNV-1a 64-bit hash.
    //
    template<typename Char, class Traits = std::char_traits<Char>>
    constexpr hash_type hash(std::basic_string_view<Char, Traits> str) {
        constexpr hash_type fnv_basis = 14695981039346656037ull;
        constexpr hash_type fnv_prime = 1099511628211ull;

        hash_type hash_value = fnv_basis;
        for (auto symbol : str) {
            hash_value ^= static_cast<hash_type>(symbol);
            hash_value *= fnv_prime;
        }

        return hash_value;
    }

    template<typename Char, class Traits = std::char_traits<Char>>
    constexpr hash_type hash(const Char* str) {
        return hash(std::basic_string_view<Char, Traits>{str});
    }

}  // namespace wheels::string

#endif  // WHEELS_STRING_HASH_HPP
