#include <catch2/catch.hpp>

#include <wheels/bits.hpp>
#include <wheels/random.hpp>
#include <wheels/string.hpp>

#include <set>


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

TEST_CASE("Generation of trash strings", "[trash string]") {
    constexpr std::size_t trash_size = 10;

    std::vector<std::string> trash;
    std::generate_n(std::back_inserter(trash), trash_size, [trash_size]() {
        return wheels::string::make_trash(trash_size);
    });

    std::set<std::string> uniques{trash.cbegin(), trash.cend()};
    REQUIRE(uniques.size() == trash.size());
    REQUIRE(wheels::random::random_select(trash.cbegin(), trash.cend())->size() == trash_size);
}

TEST_CASE("Generation of trash strings with custom charset", "[trash string]") {
    constexpr std::size_t      trash_size  = 5;
    constexpr std::string_view bad_charset = "aaaaaaaaaaa";

    std::vector<std::string> trash;
    std::generate_n(std::back_inserter(trash), trash_size, [trash_size, bad_charset]() {
        return wheels::string::make_trash(trash_size, bad_charset);
    });

    std::set<std::string> uniques{trash.cbegin(), trash.cend()};
    REQUIRE(trash.size() == trash_size);
    REQUIRE(uniques.size() == 1);
    REQUIRE(uniques.cbegin()->size() == trash_size);
}
