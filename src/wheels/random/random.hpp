#ifndef WHEELS_RANDOM_RANDOM_HPP
#define WHEELS_RANDOM_RANDOM_HPP

#include <random>
#include <type_traits>


namespace wheels::random {
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
        static std::mt19937       generator(rand_device());
        return random(min_value, max_value, generator);
    }


    template<typename Iter, typename RandomGenerator>
    Iter random_select(Iter first, Iter last, RandomGenerator& generator) {
        const std::size_t max_value = static_cast<std::size_t>(std::distance(first, last)) - 1;
        std::uniform_int_distribution<std::size_t> distribution(0, max_value);
        std::advance(first, distribution(generator));
        return first;
    }

    template<typename Iter>
    Iter random_select(Iter first, Iter last) {
        static std::random_device rand_device;
        static std::mt19937       generator(rand_device());
        return random_select(first, last, generator);
    }
}  // namespace wheels::random

#endif  // WHEELS_RANDOM_RANDOM_HPP
