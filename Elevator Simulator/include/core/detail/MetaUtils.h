// core/detail/MetaUtils.h
#ifndef CORE_DETAIL_META_UTILS_H
#define CORE_DETAIL_META_UTILS_H

#include <variant>
#include <tuple>

namespace core::detail::meta {

    template <typename Tuple>
    struct tuple_to_variant;

    template <typename... Ts>
    struct tuple_to_variant<std::tuple<Ts...>> {
        using type = std::variant<Ts...>;
    };

    template <typename Tuple>
    using tuple_to_variant_t = typename tuple_to_variant<Tuple>::type;

} // namespace core::detail::meta

#endif // CORE_DETAIL_META_UTILS_H
