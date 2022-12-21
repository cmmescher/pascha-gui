#include <pascha/output_calendars.h>

#include <pascha/calendar_conversion.h>

namespace pascha
{

Date JulianOutputCalendar::calculate(Year year) const
{
  return gregorianToJulian(calculation_method().calculate(year));
} // JulianOutputCalendar::calculate

Date GregorianOutputCalendar::calculate(Year year) const
{
  return calculation_method().calculate(year);
} // GregorianOutputCalendar::calculate

Date RevisedJulianOutputCalendar::calculate(Year year) const
{
  return gregorianToRevJulian(calculation_method().calculate(year));
} // JulianOutputCalendar::calculate

} // namespace pascha
