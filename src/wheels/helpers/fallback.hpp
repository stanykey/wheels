#ifndef WHEELS_HELPERS_FALLBACK_HPP
#define WHEELS_HELPERS_FALLBACK_HPP

#include <utility>

namespace wheels {
    template<typename Predicate, typename T>
    auto&& fallback(Predicate&&, T&& value) {
        return std::forward<T>(value);
    }

    template<typename Predicate, typename T, typename... Ts>
    auto&& fallback(Predicate&& is_invalid, T&& value, Ts&&... fallbacks) {
        return !is_invalid(value) ? std::forward<T>(value)
                                  : fallback(std::forward<Predicate>(is_invalid), std::forward<Ts>(fallbacks)...);
    }
}  // namespace wheels

#endif  // WHEELS_HELPERS_FALLBACK_HPP
