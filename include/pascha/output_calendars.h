#ifndef PASCHA_OUTPUT_CALENDARS_H
#define PASCHA_OUTPUT_CALENDARS_H 

#include "output_calendar.h"

namespace pascha
{

class JulianOutputCalendar : public OutputCalendar
{
 public:
  JulianOutputCalendar(std::shared_ptr<ICalculationMethod> calculation_method)
    : OutputCalendar{calculation_method} {}
  ~JulianOutputCalendar() = default;
  Date calculate(Year) const override;
}; // class JulianOutputCalendar

class GregorianOutputCalendar : public OutputCalendar
{
 public:
  GregorianOutputCalendar(std::shared_ptr<ICalculationMethod> calculation_method)
    : OutputCalendar{calculation_method} {}
  ~GregorianOutputCalendar() = default;
  Date calculate(Year) const override;
}; // class GregorianOutputCalendar

class RevisedJulianOutputCalendar : public OutputCalendar
{
 public:
  RevisedJulianOutputCalendar(std::shared_ptr<ICalculationMethod> calculation_method)
    : OutputCalendar{calculation_method} {}
  ~RevisedJulianOutputCalendar() = default;
  Date calculate(Year) const override;
}; // class RevisedJulianOutputCalendar

} // namespace pascha

#endif // !PASCHA_OUTPUT_CALENDARS_H
