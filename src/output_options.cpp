#include <pascha/output_options.h>

namespace pascha
{

Date ByzantineDate::calculate(Year year) const
{
  Date date{calculation_method().calculate(year)};
  date.year += 5508;
  if (date.month > 8) {
    ++date.year;
  }
  return date;
} // ByzantineDate::calculate

} // namespace pascha
