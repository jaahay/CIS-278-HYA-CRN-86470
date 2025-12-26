// core/meta/Tuple.h
#ifndef CORE_META_TUPLE_H
#define CORE_META_TUPLE_H

#include <tuple>

namespace core::meta {

    template <typename Tuple1, typename Tuple2>
    struct tuple_concat;

    template <typename... Ts1, typename... Ts2>
    struct tuple_concat<std::tuple<Ts1...>, std::tuple<Ts2...>> {
        using type = std::tuple<Ts1..., Ts2...>;
    };

    template <typename Tuple1, typename Tuple2>
    using tuple_concat_t = typename tuple_concat<Tuple1, Tuple2>::type;

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

} // namespace core::meta

#endif // CORE_META_TUPLE_H
