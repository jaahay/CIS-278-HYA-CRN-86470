#include <chrono>

#include "Utils.hpp"

std::string Utils::GenerateNanosecondString()
{
    auto since_epoch = std::chrono::system_clock::now().time_since_epoch();
    auto nanoseconds = std::chrono::duration_cast<std::chrono::nanoseconds>(since_epoch);
	auto count = nanoseconds.count() / 1'000'000'000;
    return std::to_string(count);
}
