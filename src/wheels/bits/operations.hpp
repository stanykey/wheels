#ifndef WHEELS_BITS_OPERATIONS_HPP
#define WHEELS_BITS_OPERATIONS_HPP

#include <limits>


namespace wheels::bits {
    // single bit operations
    template<typename Integer>
    constexpr bool check_bit(const Integer number, const std::uint8_t bit) noexcept {
        return (number & (Integer{1} << bit));
    }

    template<typename Integer>
    void set_bit(Integer& number, const std::uint8_t bit) noexcept {
        number |= (Integer{1} << bit);
    }

    template<typename Integer>
    void clear_bit(Integer& number, const std::uint8_t bit) noexcept {
        number &= ~(Integer{1} << bit);
    }

    template<typename Integer>
    void flip_bit(Integer& number, const std::uint8_t bit) noexcept {
        number ^= (Integer{1} << bit);
    }


    // bitmask operations
    template<typename Integer>
    constexpr bool check_mask_all(const Integer number, const Integer mask) noexcept {
        return !(~number & mask);
    }

    template<typename Integer>
    constexpr bool check_mask_any(const Integer number, const Integer mask) noexcept {
        return (number & mask);
    }

    template<typename Integer>
    void set_mask(Integer& number, const Integer mask) noexcept {
        number |= mask;
    }

    template<typename Integer>
    void clear_mask(Integer& number, const Integer mask) noexcept {
        number &= ~mask;
    }

    template<typename Integer>
    void flip_mask(Integer& number, const Integer mask) noexcept {
        number ^= mask;
    }
}  // namespace wheels::bits

#endif  // WHEELS_BITS_OPERATIONS_HPP
