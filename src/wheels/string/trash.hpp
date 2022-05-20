#ifndef WHEELS_STRING_TRASH_HPP
#define WHEELS_STRING_TRASH_HPP

#include <wheels/random/random.hpp>

#include <algorithm>
#include <iterator>
#include <string>
#include <string_view>


namespace wheels::string {
    constexpr std::string_view get_default_charset() {
        return {"abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ!@#$%^&*()_1234567890"};
    }

    std::string make_trash(std::size_t length, std::string_view charset = get_default_charset()) {
        std::string trash;
        trash.reserve(length);
        std::generate_n(std::back_inserter(trash), length, [charset] {
            const auto choice = random::random_select(charset.cbegin(), charset.cend());
            return *choice;
        });

        return trash;
    }

}  // namespace wheels::string


#endif  // WHEELS_STRING_TRASH_HPP
