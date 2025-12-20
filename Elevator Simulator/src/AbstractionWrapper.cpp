#include "AbstractionWrapper.h"
template <typename T>
inline AbstractionWrapper<T>::AbstractionWrapper(const T& obj) : ptr(std::unique_ptr<T>(obj)) {}
template <typename T>
const T& unwrap(const AbstractionWrapper<T>& wrapper)
{
	return wrapper.obj;
}
