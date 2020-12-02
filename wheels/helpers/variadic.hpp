#ifndef WHEELS_VARIADIC_HPP
#define WHEELS_VARIADIC_HPP

#include <tuple>
#include <utility>


namespace wheels {
    template <typename Callable, class... Args>
    void for_each_argument(Callable&& call_for, Args&&... args) {
        return static_cast<void>(std::initializer_list<int>{(
                call_for(std::forward<Args>(args)),
                0
            )...
        });
    }


    namespace details {
        template <typename Callable, class Tuple, std::size_t... I>
        decltype(auto) apply_impl(Callable&& call_for, Tuple&& tuple, std::index_sequence<I...>) {
            return std::forward<Callable>(call_for)(std::get<I>(std::forward<Tuple>(tuple))...);
        }

        template <typename Callable, class Tuple>
        decltype(auto) apply(Callable&& call_for, Tuple&& tuple) {
            using Indices = std::make_index_sequence<std::tuple_size<std::decay_t<Tuple>>::value>;
            return apply_impl(std::forward<Callable>(call_for), std::forward<Tuple>(tuple), Indices{});
        }
    }

    template <typename Callable, class Tuple>
    void for_tuple(Callable&& call_for, Tuple&& tuple) {
        details::apply(
            [&call_for](auto&&... xs) {
                for_each_argument(
                    call_for,
                    std::forward<decltype(xs)>(xs)...
                );
            },
            std::forward<Tuple>(tuple)
        );
    }
}

#endif //WHEELS_VARIADIC_HPP
