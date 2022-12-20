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
  int value;
  explicit Weeks(int value) : value(value) {}
}; // struct Weeks

struct Days
{
  int value;
  explicit Days(int value) : value(value) {}
}; // struct Days

} // namespace pascha

#endif // !PASCHA_DATE_H
