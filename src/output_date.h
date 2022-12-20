#ifndef PASCHA_OUTPUT_DATE_H
#define PASCHA_OUTPUT_DATE_H

#include "typedefs.h"

#include <string>

namespace pascha
{

class OutputDate
{
 public:
  virtual ~OutputDate() = default;
  virtual Year year() const = 0;
  virtual Month month() const = 0;
  virtual Day day() const = 0;
  virtual void setYear(Year year) = 0;
  virtual void setMonth(Month month) = 0;
  virtual void setDay(Day day) = 0;
}; // class IOutputDate

} // namespace pascha

#endif // !PASCHA_OUTPUT_DATE_H
