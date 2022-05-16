#ifndef WHEELS_STRING_TRASH_HPP
#define WHEELS_STRING_TRASH_HPP

#include <wheels/random/random.hpp>

#include <algorithm>
#include <iterator>
#include <string>
#include <string_view>


namespace wheels::string {
    std::string make_trash() {
        static constexpr std::size_t      MinSize = 5;
        static constexpr std::size_t      MaxSize = 25;
        static constexpr std::string_view Charset = "abcdefghijklmnopqrstuvwxyz"
                                                    "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
                                                    "!@#$%^&*()_1234567890";

        std::string trash;
        trash.reserve(random::random(MinSize, MaxSize));
        std::generate_n(std::back_inserter(trash), trash.capacity(), [&] {
            const auto choice = random::random_select(Charset.cbegin(), Charset.cend());
            return *choice;
        });

        return trash;
    }
}  // namespace wheels::string


#endif  // WHEELS_STRING_TRASH_HPP
