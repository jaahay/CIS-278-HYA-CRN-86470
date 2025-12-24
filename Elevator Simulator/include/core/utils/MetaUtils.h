// core/utils/Meta.h
#ifndef CORE_UTILS_META_UTILS_H
#define CORE_UTILS_META_UTILS_H

#include <variant>
#include <tuple>
#include <type_traits>

namespace core::utils {

    // --- tuple_to_variant ---
    // Converts std::tuple<Ts...> to std::variant<Ts...>
    template <typename Tuple>
    struct tuple_to_variant;

    template <typename... Ts>
    struct tuple_to_variant<std::tuple<Ts...>> {
        using type = std::variant<Ts...>;
    };

    template <typename Tuple>
    using tuple_to_variant_t = typename tuple_to_variant<Tuple>::type;

    // --- tuple_concat ---
    // Concatenates two tuples into one
    template <typename Tuple1, typename Tuple2>
    struct tuple_concat;

    template <typename... Ts1, typename... Ts2>
    struct tuple_concat<std::tuple<Ts1...>, std::tuple<Ts2...>> {
        using type = std::tuple<Ts1..., Ts2...>;
    };

    template <typename Tuple1, typename Tuple2>
    using tuple_concat_t = typename tuple_concat<Tuple1, Tuple2>::type;

    // --- tuple_concat_many ---
    // Concatenates multiple tuples recursively
    template <typename... Tuples>
    struct tuple_concat_many;

    template <>
    struct tuple_concat_many<> {
        using type = std::tuple<>;
    };

    template <typename T>
    struct tuple_concat_many<T> {
        using type = T;
    };

    template <typename T1, typename T2, typename... Ts>
    struct tuple_concat_many<T1, T2, Ts...> {
        using type = typename tuple_concat_many<
            tuple_concat_t<T1, T2>,
            Ts...
        >::type;
    };

    template <typename... Tuples>
    using tuple_concat_many_t = typename tuple_concat_many<Tuples...>::type;

    // --- variant_concat ---
    // Compose a variant from multiple variants by concatenating their alternative types
    template <typename... Variants>
    struct variant_concat {
    private:
        using concatenated_tuple = tuple_concat_many_t<typename tuple_to_variant<Variants>::type...>;
    public:
        using type = tuple_to_variant_t<concatenated_tuple>;
    };

    template <typename... Variants>
    using variant_concat_t = typename variant_concat<Variants...>::type;

} // namespace core::utils

#endif // CORE_UTILS_META_UTILS_H
