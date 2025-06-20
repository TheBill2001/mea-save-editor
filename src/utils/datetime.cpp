#include "datetime.hpp"

namespace
{

constexpr auto unixSecJulianDelta = 210866803200;

}

namespace Utils::DateTime
{

quint64 toJulianSeconds(const QDateTime &dateTime)
{
    return (dateTime.isValid() ? dateTime.toSecsSinceEpoch() : 0) + unixSecJulianDelta;
}

QDateTime fromJulianSeconds(quint64 julianSeconds)
{
    // fromSecsSinceEpoch take signed 64bit integer. We won't ever get there in this life time :D.
    return QDateTime::fromSecsSinceEpoch(julianSeconds - unixSecJulianDelta);
}

} // namespace Utils::DateTime
