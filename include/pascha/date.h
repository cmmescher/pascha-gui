#ifndef PASCHA_DATE_H
#define PASCHA_DATE_H

#include "typedefs.h"

namespace pascha
{

struct Date
{
  Year year;
  Month month;
  Day day;
}; // struct Date

struct Weeks
{
    std::int64_t value;
  explicit Weeks(std::int64_t value) : value(value) {}
}; // struct Weeks

struct Days
{
  std::int64_t value;
  explicit Days(std::int64_t value) : value(value) {}
}; // struct Days

} // namespace pascha

#endif // !PASCHA_DATE_H
