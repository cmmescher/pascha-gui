#ifndef PASCHA_OUTPUT_CALENDARS_H
#define PASCHA_OUTPUT_CALENDARS_H 

#include "output_calendar.h"

namespace pascha
{

class JulianOutputCalendar : public OutputCalendar
{
 public:
  JulianOutputCalendar(std::unique_ptr<ICalculationMethod> calculation_method)
    : OutputCalendar(std::move(calculation_method)) {}
  Date calculate(Year) const override;
}; // class JulianOutputCalendar

class GregorianOutputCalendar : public OutputCalendar
{
 public:
  GregorianOutputCalendar(std::unique_ptr<ICalculationMethod> calculation_method)
    : OutputCalendar(std::move(calculation_method)) {}
  Date calculate(Year) const override;
}; // class GregorianOutputCalendar

class RevisedJulianOutputCalendar : public OutputCalendar
{
 public:
  RevisedJulianOutputCalendar(std::unique_ptr<ICalculationMethod> calculation_method)
    : OutputCalendar(std::move(calculation_method)) {}
  Date calculate(Year) const override;
}; // class RevisedJulianOutputCalendar

} // namespace pascha

#endif // !PASCHA_OUTPUT_CALENDARS_H
