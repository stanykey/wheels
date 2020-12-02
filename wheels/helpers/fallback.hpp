#ifndef WHEELS_HELPERS_FALLBACK_HPP
#define WHEELS_HELPERS_FALLBACK_HPP

#include <utility>


namespace wheels {
    template <typename Predicate, typename T, typename... Ts>
    T fallback(Predicate&& fail_with, T&& value, Ts&&... fallbacks) {
        return !fail_with(value)
            ? std::forward<T>(value)
            : fallback(std::forward<Predicate>(fail_with), std::forward<Ts>(fallbacks)...)
        ;
    }

    template<typename Predicate, typename T>
    T fallback(Predicate, T&& value)
    {
        return value;
    }
}

#endif //WHEELS_HELPERS_FALLBACK_HPP
