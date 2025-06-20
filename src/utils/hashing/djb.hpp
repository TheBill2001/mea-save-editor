#ifndef DJB2_HPP
#define DJB2_HPP

#include <QtTypes>

namespace Utils::Hashing
{

/**
 * This function is not the standard DJB2 hashing function.
 * The standards
 * ```
 * hash *= 33;
 * hash += c;
 * ```
 */
constexpr quint32 djbHash(const char *str)
{
    quint32 hash = 5381;
    quint8 c;

    while ((c = *str++)) {
        hash *= 33;
        hash ^= c;
    }

    return hash;
}

}

#endif // DJB2_HPP
