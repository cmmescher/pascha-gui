#include "pascha/calendar_conversion.h"

#include <catch2/catch_test_macros.hpp>

TEST_CASE("Gregorian date to JDN")
{
  using namespace pascha;

  SECTION("Positive year")
  {
    Date date{2019, 1, 1};
    REQUIRE(gregorianToJdn(date) == 2458485);
  }

  SECTION("Zero year (1 BC)")
  {
    Date date{0, 1, 1};
    REQUIRE(gregorianToJdn(date) == 1721060);
  }

  SECTION("Negative year")
  {
    Date date{-1, 1, 1};
    REQUIRE(gregorianToJdn(date) == 1720695);
  }

  SECTION("Positive year, leap day")
  {
    Date date{2020, 2, 29};
    REQUIRE(gregorianToJdn(date) == 2458909);
  }

  SECTION("Zero year (1 BC), leap day")
  {
    Date date{0, 2, 29};
    REQUIRE(gregorianToJdn(date) == 1721119);
  }

  SECTION("Negative year, leap day")
  {
    Date date{-1, 2, 29};
    REQUIRE(gregorianToJdn(date) == 1720754);
  }
}

TEST_CASE("Gregorian to Julian conversion")
{
  using namespace pascha;

  SECTION("Positive year")
  {
    Date date{2019, 1, 1};
    date = gregorianToJulian(date);
    REQUIRE(date.year == 2018);
    REQUIRE(date.month == 12);
    REQUIRE(date.day == 19);
  }

  SECTION("Zero year (1 BC)")
  {
    Date date{0, 1, 1};
    date = gregorianToJulian(date);
    REQUIRE(date.year == 0);
    REQUIRE(date.month == 1);
    REQUIRE(date.day == 3);
  }

  SECTION("Negative year")
  {
    Date date{-1, 1, 1};
    date = gregorianToJulian(date);
    REQUIRE(date.year == -1);
    REQUIRE(date.month == 1);
    REQUIRE(date.day == 3);
  }

  SECTION("Positive year, leap day")
  {
    Date date{2020, 2, 29};
    date = gregorianToJulian(date);
    REQUIRE(date.year == 2020);
    REQUIRE(date.month == 2);
    REQUIRE(date.day == 16);
  }

  SECTION("Zero year (1 BC), leap day")
  {
    Date date{0, 2, 29};
    date = gregorianToJulian(date);
    REQUIRE(date.year == 0);
    REQUIRE(date.month == 3);
    REQUIRE(date.day == 2);
  }

  SECTION("Negative year, leap day")
  {
    Date date{-1, 2, 29};
    date = gregorianToJulian(date);
    REQUIRE(date.year == -1);
    REQUIRE(date.month == 3);
    REQUIRE(date.day == 3);
  }

  SECTION("Gregorian non-leap year to Julian leap year")
  {
    Date date{2100, 3, 1};
    date = gregorianToJulian(date);
    REQUIRE(date.year == 2100);
    REQUIRE(date.month == 2);
    REQUIRE(date.day == 16);
  }
}

TEST_CASE("Julian to Gregorian conversion")
{
  using namespace pascha;

  SECTION("Positive year")
  {
    Date date{2019, 1, 1};
    date = julianToGregorian(date);
    REQUIRE(date.year == 2019);
    REQUIRE(date.month == 1);
    REQUIRE(date.day == 14);
  }

  SECTION("Zero year (1 BC)")
  {
    Date date{0, 1, 1};
    date = julianToGregorian(date);
    REQUIRE(date.year == -1);
    REQUIRE(date.month == 12);
    REQUIRE(date.day == 30);
  }

  SECTION("Negative year")
  {
    Date date{-1, 1, 1};
    date = julianToGregorian(date);
    REQUIRE(date.year == -2);
    REQUIRE(date.month == 12);
    REQUIRE(date.day == 30);
  }

  SECTION("Positive year, leap day")
  {
    Date date{2020, 2, 29};
    date = julianToGregorian(date);
    REQUIRE(date.year == 2020);
    REQUIRE(date.month == 3);
    REQUIRE(date.day == 13);
  }

  SECTION("Zero year (1 BC), leap day")
  {
    Date date{0, 2, 29};
    date = julianToGregorian(date);
    REQUIRE(date.year == 0);
    REQUIRE(date.month == 2);
    REQUIRE(date.day == 27);
  }

  SECTION("Negative year, leap day")
  {
    Date date{-1, 2, 29};
    date = julianToGregorian(date);
    REQUIRE(date.year == -1);
    REQUIRE(date.month == 2);
    REQUIRE(date.day == 27);
  }

  SECTION("Julian leap year to Gregorian non-leap year")
  {
    Date date{2100, 2, 16};
    date = julianToGregorian(date);
    REQUIRE(date.year == 2100);
    REQUIRE(date.month == 3);
    REQUIRE(date.day == 1);
  }
}

TEST_CASE("Gregorian to Revised Julian conversion")
{
  using namespace pascha;

  SECTION("Positive year")
  {
    Date date{2019, 1, 1};
    date = gregorianToRevJulian(date);
    REQUIRE(date.year == 2019);
    REQUIRE(date.month == 1);
    REQUIRE(date.day == 1);
  }

  SECTION("Large Positive year (for calendar divergence)")
  {
    Date date{10019, 1, 1};
    date = gregorianToRevJulian(date);
    REQUIRE(date.year == 10019);
    REQUIRE(date.month == 1);
    REQUIRE(date.day == 4);
  }

  SECTION("Zero year (1 BC)")
  {
    Date date{0, 1, 1};
    date = gregorianToRevJulian(date);
    REQUIRE(date.year == -1);
    REQUIRE(date.month == 12);
    REQUIRE(date.day == 31);
  }

  SECTION("Negative year")
  {
    Date date{-1, 1, 1};
    date = gregorianToRevJulian(date);
    REQUIRE(date.year == -2);
    REQUIRE(date.month == 12);
    REQUIRE(date.day == 31);
  }

  SECTION("Positive year, leap day")
  {
    Date date{2020, 2, 29};
    date = gregorianToRevJulian(date);
    REQUIRE(date.year == 2020);
    REQUIRE(date.month == 2);
    REQUIRE(date.day == 29);
  }

  SECTION("Large Positive year (for calendar divergence), leap day")
  {
    Date date{10020, 2, 29};
    date = gregorianToRevJulian(date);
    REQUIRE(date.year == 10020);
    REQUIRE(date.month == 3);
    REQUIRE(date.day == 3);
  }

  SECTION("Zero year (1 BC), leap day")
  {
    Date date{0, 2, 29};
    date = gregorianToRevJulian(date);
    REQUIRE(date.year == 0);
    REQUIRE(date.month == 2);
    REQUIRE(date.day == 28);
  }

  SECTION("Negative year, leap day")
  {
    Date date{-1, 2, 29};
    date = gregorianToRevJulian(date);
    REQUIRE(date.year == -1);
    REQUIRE(date.month == 2);
    REQUIRE(date.day == 28);
  }

  SECTION("Gregorian non-leap year to Revised Julian leap year")
  {
    Date date{2900, 2, 28};
    date = gregorianToRevJulian(date);
    REQUIRE(date.year == 2900);
    REQUIRE(date.month == 2);
    REQUIRE(date.day == 29);
  }

  SECTION("Gregorian leap year to Revised Julian non-leap year")
  {
    Date date{2800, 2, 29};
    date = gregorianToRevJulian(date);
    REQUIRE(date.year == 2800);
    REQUIRE(date.month == 3);
    REQUIRE(date.day == 1);
  }
}

TEST_CASE("Revised Julian to Gregorian conversion")
{
  using namespace pascha;

  SECTION("Positive year")
  {
    Date date{2019, 1, 1};
    date = revJulianToGregorian(date);
    REQUIRE(date.year == 2019);
    REQUIRE(date.month == 1);
    REQUIRE(date.day == 1);
  }

  SECTION("Large Positive year (for calendar divergence)")
  {
    Date date{10019, 1, 1};
    date = revJulianToGregorian(date);
    REQUIRE(date.year == 10018);
    REQUIRE(date.month == 12);
    REQUIRE(date.day == 29);
  }

  SECTION("Zero year (1 BC)")
  {
    Date date{0, 1, 1};
    date = revJulianToGregorian(date);
    REQUIRE(date.year == 0);
    REQUIRE(date.month == 1);
    REQUIRE(date.day == 2);
  }

  SECTION("Negative year")
  {
    Date date{-1, 1, 1};
    date = revJulianToGregorian(date);
    REQUIRE(date.year == -1);
    REQUIRE(date.month == 1);
    REQUIRE(date.day == 2);
  }

  SECTION("Positive year, leap day")
  {
    Date date{2020, 2, 29};
    date = revJulianToGregorian(date);
    REQUIRE(date.year == 2020);
    REQUIRE(date.month == 2);
    REQUIRE(date.day == 29);
  }

  SECTION("Large Positive year (for calendar divergence), leap day")
  {
    Date date{10020, 2, 29};
    date = revJulianToGregorian(date);
    REQUIRE(date.year == 10020);
    REQUIRE(date.month == 2);
    REQUIRE(date.day == 26);
  }

  SECTION("Zero year (1 BC), leap day")
  {
    Date date{0, 2, 29};
    date = revJulianToGregorian(date);
    REQUIRE(date.year == 0);
    REQUIRE(date.month == 3);
    REQUIRE(date.day == 1);
  }

  SECTION("Negative year, leap day")
  {
    Date date{-1, 2, 29};
    date = revJulianToGregorian(date);
    REQUIRE(date.year == -1);
    REQUIRE(date.month == 3);
    REQUIRE(date.day == 2);
  }

  SECTION("Revised Julian non-leap year to Gregorian leap year")
  {
    Date date{2800, 3, 1};
    date = revJulianToGregorian(date);
    REQUIRE(date.year == 2800);
    REQUIRE(date.month == 2);
    REQUIRE(date.day == 29);
  }

  SECTION("Revised Julian leap year to Gregorian non-leap year")
  {
    Date date{2900, 2, 29};
    date = revJulianToGregorian(date);
    REQUIRE(date.year == 2900);
    REQUIRE(date.month == 2);
    REQUIRE(date.day == 28);
  }
}
