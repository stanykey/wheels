#include <catch2/catch.hpp>

#include <wheels/bits.hpp>


TEST_CASE("Single bits operations", "[bits]") {
    std::uint8_t number = 0;

    wheels::bits::set_bit(number, 0);
    REQUIRE(wheels::bits::check_bit(number, 0));

    wheels::bits::flip_bit(number, 3);
    REQUIRE(wheels::bits::check_bit(number, 3));

    wheels::bits::clear_bit(number, 0);
    REQUIRE(!wheels::bits::check_bit(number, 0));
}

TEST_CASE("Bit mask operations", "[bits]") {
    constexpr std::uint16_t mask1 = 0b10101;
    constexpr std::uint16_t mask2 = 0b00101;

    std::uint16_t number = 0;
    REQUIRE(!wheels::bits::check_mask_all(number, mask1));

    wheels::bits::set_mask(number, mask1);
    REQUIRE(wheels::bits::check_mask_all(number, mask1));

    wheels::bits::clear_mask(number, mask2);
    REQUIRE(wheels::bits::check_mask_any(number, mask1));
    REQUIRE(!wheels::bits::check_mask_any(number, mask2));

    wheels::bits::flip_mask(number, mask1);
    REQUIRE(wheels::bits::check_mask_any(number, mask1));
    REQUIRE(wheels::bits::check_mask_all(number, mask2));
}
