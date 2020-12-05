
#ifndef WHEELS_VARIANT_OVERLOAD_HPP
#define WHEELS_VARIANT_OVERLOAD_HPP


namespace wheels {
    template<class... Ts>
    struct overload : Ts... {
        using Ts::operator()...;
    };

    template<class... Ts>
    overload(Ts...) -> overload<Ts...>;
}

#endif //WHEELS_VARIANT_OVERLOAD_HPP
