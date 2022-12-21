#ifndef PASCHA_CALENDAR_CONVERSION_H
#define PASCHA_CALENDAR_CONVERSION_H

#include "date.h"

namespace pascha
{

using CalcInt = std::int64_t;

CalcInt gregorianToJdn(const Date& date);
Date gregorianToJulian(const Date& date);
Date julianToGregorian(const Date& date);
Date gregorianToRevJulian(const Date& date);
Date revJulianToGregorian(const Date& date);

} // namespace pascha

#endif // !PASCHA_CALENDAR_CONVERSION_H