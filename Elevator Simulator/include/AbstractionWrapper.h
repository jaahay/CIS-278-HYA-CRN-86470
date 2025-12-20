#ifndef ABSTRACTION_WRAPPER_H
#define ABSTRACTION_WRAPPER_H
#include <memory>
#include <type_traits>
//template <typename BaseType>
//concept Abstraction = std::is_abstract_v<BaseType>;
//template <typename Type>
//concept Const = std::is_const_v<Type>;
//template <typename Type>
//concept ConstAbstraction = (Abstraction<Type> && Const<Type>);

template <typename T>
class AbstractionWrapper;

template <typename T>
const T& unwrap(const AbstractionWrapper<T>& wrapper);

template <typename T>
class AbstractionWrapper
{
public:
	explicit AbstractionWrapper(const T&);
	friend const T& unwrap<>(const AbstractionWrapper<T>&);
private:
	std::unique_ptr<T> ptr;
};
#endif // !ABSTRACTION_WRAPPER_H
