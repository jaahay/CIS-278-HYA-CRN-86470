#include <variant>
#include <iostream>
#include <type_traits>
#include <stdexcept>

template<typename T>
constexpr bool always_false = false;

struct Base { virtual ~Base() = default; };
struct DerivedA : Base {};
struct DerivedB : Base {};

using Variant = std::variant<const DerivedA*, const DerivedB*>;

int main() {
    Variant v = &DerivedA{};

    auto result = std::visit([](auto&& ptr) {
        using T = std::decay_t<decltype(*ptr)>;
        if constexpr (std::is_same_v<T, DerivedA>) {
            std::cout << "DerivedA\n";
            return 1;
        }
        else if constexpr (std::is_same_v<T, DerivedB>) {
            std::cout << "DerivedB\n";
            return 2;
        }
        else {
            throw std::logic_error("Unhandled type");
        }
        }, v);

    std::cout << "Result: " << result << "\n";
}