#ifndef UTILS_NUMBER_HPP
#define UTILS_NUMBER_HPP

#include <QtTypes>

namespace Utils::Number
{

template<typename T>
constexpr T swapEndian(T src)
    requires(std::is_integral_v<T>)
{
    T result = 0;
    for (std::size_t i = 0; i < sizeof(T); ++i) {
        result = (result << 8) | (src & 0xFFu);
        src >>= 8;
    }
    return result;
}

} // namespace Utils::Number

#endif // UTILS_NUMBER_HPP
