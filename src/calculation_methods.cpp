#include "pascha/calculation_methods.h"

#include "pascha/calendar_conversion.h"
#include "pascha/typedefs.h"

namespace pascha
{

Date JulianCalculationMethod::calculate(Year year) const
{
  CalcInt a = year % 4;
  CalcInt b = year % 7;
  CalcInt c = year % 19;
  CalcInt d = (19 * c + 15) % 30;
  CalcInt e = (2 * a + 4 * b - d + 34) % 7;
  CalcInt month = (d + e + 114) / 31;
  CalcInt day = (d + e + 114) % 31 + 1;
  return julianToGregorian(Date{year, static_cast<Month>(month), static_cast<Day>(day)});
} // JulianCalculationMethod::calculate

Date GregorianCalculationMethod::calculate(Year year) const
{
  CalcInt a = year % 19;
  CalcInt b = year / 100;
  CalcInt c = year % 100;
  CalcInt d = b / 4;
  CalcInt e = b % 4;
  CalcInt f = (b + 8) / 25;
  CalcInt g = (b - f + 1) / 3;
  CalcInt h = (19 * a + b - d - g + 15) % 30;
  CalcInt i = c / 4;
  CalcInt k = c % 4;
  CalcInt l = (32 + 2 * e + 2 * i - h - k) % 7;
  CalcInt m = (a + 11 * h + 22 * l) / 451;
  CalcInt month = (h + l - 7 * m + 114) / 31;
  CalcInt day = ((h + l - 7 * m + 114) % 31) + 1;
  return Date{year, static_cast<Month>(month), static_cast<Day>(day)};
} // GregorianCalculationMethod::calculate

} // namespace pascha
