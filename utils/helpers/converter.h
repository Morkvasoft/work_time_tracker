#ifndef CONVERTER_H_
#define CONVERTER_H_

#include <QDate>
#include <QString>

namespace converter
{

inline QString dateToString(const QDate& date)
{
    return date.toString("yyyy-MM-dd");
}

} // namespace utils

#endif // CONVERTER_H_