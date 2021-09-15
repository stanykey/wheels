#ifndef WHEELS_RANDOM_RANDOM_HPP
#define WHEELS_RANDOM_RANDOM_HPP

#include <random>
#include <type_traits>


namespace wheels {
    namespace random {
        template<typename Int, typename RandomGenerator>
        Int random(Int min_value, Int max_value, RandomGenerator& generator) {
            static_assert(std::is_integral<Int>::value, "Function supports only integral types");

            std::uniform_int_distribution<Int> distribution(min_value, max_value);
            return distribution(generator);
        }

        template<typename Int>
        Int random(Int min_value, Int max_value) {
            static_assert(std::is_integral<Int>::value, "Function supports only integral types");

            static std::random_device rand_device;
            static std::mt19937 generator(rand_device());
            return random(min_value, max_value, generator);
        }


        template<typename Iter, typename RandomGenerator>
        Iter random_select(Iter first, Iter last, RandomGenerator& generator) {
            std::uniform_int_distribution<> distribution(0, static_cast<int>(std::distance(first, last) - 1));
            std::advance(first, distribution(generator));
            return first;
        }

        template<typename Iter>
        Iter random_select(Iter first, Iter last) {
            static std::random_device rand_device;
            static std::mt19937 generator(rand_device());
            return random_select(first, last, generator);
        }
    }
}

#endif //WHEELS_RANDOM_RANDOM_HPP