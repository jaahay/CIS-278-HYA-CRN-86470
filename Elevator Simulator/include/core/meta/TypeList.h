// core/meta/TypeList.h
#ifndef CORE_META_TYPELIST_H
#define CORE_META_TYPELIST_H

#include <type_traits>

namespace core::meta {

    // Simple typelist container
    template <typename... Ts>
    struct TypeList {};

    // Check if a type T is contained in TypeList
    template <typename T, typename List>
    struct Contains;

    template <typename T>
    struct Contains<T, TypeList<>> : std::false_type {};

    template <typename T, typename Head, typename... Tail>
    struct Contains<T, TypeList<Head, Tail...>> : std::conditional_t<
        std::is_same_v<T, Head>,
        std::true_type,
        Contains<T, TypeList<Tail...>>
    > {
    };

    // Append a type T to a TypeList
    template <typename List, typename T>
    struct Append;

    template <typename... Ts, typename T>
    struct Append<TypeList<Ts...>, T> {
        using type = TypeList<Ts..., T>;
    };

} // namespace core::meta

#endif // CORE_META_TYPELIST_H
