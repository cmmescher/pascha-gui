#include "pascha/target_date.h"

#include <ctime>
#include <iostream>

namespace pascha
{

void TargetDate::shift(int days, Date& date) const
{
  std::tm t{};
  t.tm_year = date.year - 1900;
  t.tm_mon = date.month - 1;
  t.tm_mday = date.day + days;

  std::mktime(&t);

  date.year = t.tm_year + 1900;
  date.month = t.tm_mon + 1;
  date.day = t.tm_mday;
}

Date TargetDate::calculate(Year year) const
{
  Date date = calculation_method().calculate(year);
  shift(m_shift_amount, date);
  return date;
}

} // namespace pascha
