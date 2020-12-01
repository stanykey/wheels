#ifndef WHEELS_STRING_TRASH_HPP
#define WHEELS_STRING_TRASH_HPP

#include <string>
#include <iterator>
#include <algorithm>

#include <wheels/random/random.hpp>


namespace wheels {
    namespace string {
        std::string make_trash() {
            std::string trash;
            trash.reserve(random::random(5, 25));
            std::generate_n(std::back_inserter(trash), trash.capacity(), [&] {
                static std::string const charset = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ!@#$%^&*()_1234567890";
                auto const it = random::random_select(std::cbegin(charset), std::cend(charset));
                return *it;
            });

            return trash;
        }
    }
}


#endif //WHEELS_STRING_TRASH_HPP
