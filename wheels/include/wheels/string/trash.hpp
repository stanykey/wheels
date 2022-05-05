#ifndef WHEELS_STRING_TRASH_HPP
#define WHEELS_STRING_TRASH_HPP

#include <wheels/random/random.hpp>

#include <algorithm>
#include <iterator>
#include <string>


namespace wheels::string {
    std::string make_trash() {
        static constexpr std::size_t min_size = 5;
        static constexpr std::size_t max_size = 25;

        std::string trash;
        trash.reserve(random::random(min_size, max_size));
        std::generate_n(std::back_inserter(trash), trash.capacity(), [&] {
            static const std::string charset =
                "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ!@#$%^&*()_1234567890";
            const auto it = random::random_select(std::cbegin(charset), std::cend(charset));
            return *it;
        });

        return trash;
    }
}  // namespace wheels::string


#endif  // WHEELS_STRING_TRASH_HPP
