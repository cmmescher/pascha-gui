#include "pascha/calculation_methods.h"

#include <catch2/catch_test_macros.hpp>

TEST_CASE("Positive year")
{
  using namespace pascha;

  Year year{2019};

  SECTION("Julian calculation")
  {
    JulianCalculationMethod method{};
    Date date{method.calculate(year)};
    REQUIRE(date.year == 2019);
    REQUIRE(date.month == 4);
    REQUIRE(date.day == 28);
  } // Julian calculation

  SECTION("Gregorian calculation")
  {
    GregorianCalculationMethod method{};
    Date date{method.calculate(year)};
    REQUIRE(date.year == 2019);
    REQUIRE(date.month == 4);
    REQUIRE(date.day == 21);
  } // Gregorian calculation
} // Positive year

TEST_CASE("Zero year (1 BC)")
{
  using namespace pascha;

  Year year{0};

  SECTION("Julian calculation")
  {
    JulianCalculationMethod method{};
    Date date{method.calculate(year)};
    REQUIRE(date.year == 0);
    REQUIRE(date.month == 4);
    REQUIRE(date.day == 9);
  } // Julian calculation

  SECTION("Gregorian calculation")
  {
    GregorianCalculationMethod method{};
    Date date{method.calculate(year)};
    REQUIRE(date.year == 0);
    REQUIRE(date.month == 4);
    REQUIRE(date.day == 9);
  } // Gregorian calculation
} // Zero year (1 BC)

TEST_CASE("Negative year")
{
  using namespace pascha;

  Year year{-1};

  SECTION("Julian calculation")
  {
    JulianCalculationMethod method{};
    Date date{method.calculate(year)};
    REQUIRE(date.year == -1);
    REQUIRE(date.month == 3);
    REQUIRE(date.day == 20);
  } // Julian calculation

  SECTION("Gregorian calculation")
  {
    GregorianCalculationMethod method{};
    Date date{method.calculate(year)};
    REQUIRE(date.year == -1);
    REQUIRE(date.month == 3);
    REQUIRE(date.day == 20);
  } // Gregorian calculation
}
