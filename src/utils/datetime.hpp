#ifndef UTILS_DATETIME_HPP
#define UTILS_DATETIME_HPP

#include <QDateTime>

namespace Utils::DateTime
{

QDateTime fromJulianSeconds(quint64);
quint64 toJulianSeconds(const QDateTime &);

} // namespace Utils::DateTime

#endif // UTILS_DATETIME_HPP
