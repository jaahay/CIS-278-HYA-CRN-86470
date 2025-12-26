// core/meta/Variant.h
#ifndef CORE_META_VARIANT_H
#define CORE_META_VARIANT_H

#include <variant>
#include <tuple>
#include "Tuple.h"

namespace core::meta {

    template <typename Tuple>
    struct tuple_to_variant;

    template <typename... Ts>
    struct tuple_to_variant<std::tuple<Ts...>> {
        using type = std::variant<Ts...>;
    };

    template <typename Tuple>
    using tuple_to_variant_t = typename tuple_to_variant<Tuple>::type;

    template <typename... Variants>
    struct variant_concat {
    private:
        using concatenated_tuple = tuple_concat_many_t<typename tuple_to_variant<Variants>::type...>;
    public:
        using type = tuple_to_variant_t<concatenated_tuple>;
    };

    template <typename... Variants>
    using variant_concat_t = typename variant_concat<Variants...>::type;

} // namespace core::meta

#endif // CORE_META_VARIANT_H
