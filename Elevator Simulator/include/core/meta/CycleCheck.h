// core/meta/CycleCheck.h
#ifndef CORE_META_CYCLE_CHECK_H
#define CORE_META_CYCLE_CHECK_H

#include "TypeList.h"  // Your existing TypeList utilities
#include <type_traits>

namespace core::meta {

    // Forward declaration
    template <typename T, typename Visited = TypeList<>>
    struct CheckNoCycle;

    // Helper: Check if T is in Visited list
    template <typename T, typename Visited>
    struct CheckNoCycle {
        static_assert(!Contains<T, Visited>::value, "Cycle detected in priority ordering!");

        using NewVisited = typename Append<Visited, T>::type;

        // Check all types T is higher than
        template <typename List>
        struct CheckList;

        template <>
        struct CheckList<TypeList<>> {
            static constexpr bool value = true;
        };

        template <typename Head, typename... Tail>
        struct CheckList<TypeList<Head, Tail...>> {
            static constexpr bool value =
                CheckNoCycle<Head, NewVisited>::value&& CheckList<TypeList<Tail...>>::value;
        };

        static constexpr bool value = CheckList<typename T::HigherThanList>::value;
    };

} // namespace core::meta

#endif // CORE_META_CYCLE_CHECK_H
