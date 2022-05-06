#include <catch2/catch.hpp>

#include <wheels/bits.hpp>


TEST_CASE("Single bits operations with constexpr", "[bits]") {
    constexpr std::uint64_t zero{0};

    STATIC_REQUIRE(!wheels::bits::check_bit(zero, 0));

    constexpr std::uint32_t five = 0b101;
    STATIC_REQUIRE(five == 5);
    STATIC_REQUIRE(wheels::bits::check_bit(five, 0));
    STATIC_REQUIRE(wheels::bits::check_bit(five, 2));
}

TEST_CASE("Bit mask operations with constexpr", "[bits]") {
    constexpr std::uint64_t mask = 0b101;
    constexpr std::uint64_t four = 4;
    constexpr std::uint64_t five = 5;

    STATIC_REQUIRE(!wheels::bits::check_mask_all(four, mask));
    STATIC_REQUIRE(wheels::bits::check_mask_all(five, mask));

    STATIC_REQUIRE(wheels::bits::check_mask_any(four, mask));
    STATIC_REQUIRE(wheels::bits::check_mask_any(five, mask));
}
