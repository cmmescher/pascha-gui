#ifndef PASCHA_CALCULATION_OPTIONS_H
#define PASCHA_CALCULATION_OPTIONS_H

#include "typedefs.h"

#include <vector>

namespace pascha
{

using ECalculationMethod = int;
using EOutputCalendar = int;
using ETargetOutput = int;
using EOutputOption = int;

struct CalculationOptions
{
  ECalculationMethod calculation_method;
  ETargetOutput target_output;
  EOutputCalendar output_calendar;
  std::vector<EOutputOption> options;
  Year year;
}; // struct CalculationOptions


namespace e_calculation_method
{

enum {
  julian = 0,
  gregorian,
  last, // for extentions
}; // enum

} // namespace ECalculationMethod

namespace e_target_output
{

enum {
  pascha = 0,
  daysUntil,
  weeksBetween,
  meatfare,
  cheesefare,
  ashWednesday,
  midfeastPentecost,
  leavetakingPascha,
  ascension,
  pentecost,
  last, // for extentions
}; // enum

} // namespace e_target_date

namespace e_output_calendar
{

enum {
  julian = 0,
  gregorian,
  rev_julian,
  last, // for extentions
}; // enum

} // namespace e_output_calendar

namespace e_output_option
{

enum {
  byzantine = 0,
  last, // for extentions
}; // enum

} // namespace e_output_option

} // namespace pascha

#endif // !PASCHA_CALCULATION_OPTIONS_H
