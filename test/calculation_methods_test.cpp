// Copyright (C) 2022, 2024 Christopher Michael Mescher
//
// pascha-lib: A library for calculating the date of Pascha (Easter).
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>.
//
// Contact !(echo \<pascha-mescher+faith\>|sed s/\+/./g\;s/\-/@/) for bug
// reporting.

#include "pascha/calculation_methods.h"
#include "pascha/output_calendars.h"
#include "pascha/output_options.h"
#include "pascha/target_dates.h"

#include <catch2/catch_test_macros.hpp>

#include <memory>

TEST_CASE("Julian Calculation")
{
  using namespace pascha;

  Year posYear{2019};
  Year zeroYear{0};
  Year negYear{-1};

  std::shared_ptr<ICalculationMethod> method{std::make_unique<JulianCalculationMethod>()};

  SECTION("Pascha")
  {
    SECTION("Gregorian Output Calendar")
    {
      SECTION("A.D. Style year")
      {
        Date posDate{method->calculate(posYear)};
        REQUIRE(posDate.year == 2019);
        REQUIRE(posDate.month == 4);
        REQUIRE(posDate.day == 28);

        Date zeroDate{method->calculate(zeroYear)};
        REQUIRE(zeroDate.year == 0);
        REQUIRE(zeroDate.month == 4);
        REQUIRE(zeroDate.day == 9);

        Date negDate{method->calculate(negYear)};
        REQUIRE(negDate.year == -1);
        REQUIRE(negDate.month == 3);
        REQUIRE(negDate.day == 20);
      } // Julian Calculation - Pascha - Gregorian Output Calendar - A.D. Style year

      SECTION("Byzantine Style year")
      {
        std::shared_ptr<ICalculationMethod> byzantine{std::make_shared<ByzantineDate>(method)};

        Date posDate{byzantine->calculate(posYear)};
        REQUIRE(posDate.year == 7527);
        REQUIRE(posDate.month == 4);
        REQUIRE(posDate.day == 28);

        Date zeroDate{byzantine->calculate(zeroYear)};
        REQUIRE(zeroDate.year == 5508);
        REQUIRE(zeroDate.month == 4);
        REQUIRE(zeroDate.day == 9);

        Date negDate{byzantine->calculate(negYear)};
        REQUIRE(negDate.year == 5507);
        REQUIRE(negDate.month == 3);
        REQUIRE(negDate.day == 20);
      } // Julian Calculation - Pascha - Gregorian Output Calendar - B.C. Style year
    } // Julian Calculation - Pascha - Gregorian Output Calendar

    SECTION("Julian Output Calendar")
    {
      std::shared_ptr<ICalculationMethod> outputCalendar{std::make_shared<JulianOutputCalendar>(method)};

      SECTION("A.D. Style year")
      {
        Date posDate{outputCalendar->calculate(posYear)};
        REQUIRE(posDate.year == 2019);
        REQUIRE(posDate.month == 4);
        REQUIRE(posDate.day == 15);

        Date zeroDate{outputCalendar->calculate(zeroYear)};
        REQUIRE(zeroDate.year == 0);
        REQUIRE(zeroDate.month == 4);
        REQUIRE(zeroDate.day == 11);

        Date negDate{outputCalendar->calculate(negYear)};
        REQUIRE(negDate.year == -1);
        REQUIRE(negDate.month == 3);
        REQUIRE(negDate.day == 22);
      } // Julian Calculation - Pascha - Julian Output Calendar - A.D. Style year

      SECTION("Byzantine Style year")
      {
        std::shared_ptr<ICalculationMethod> byzantine{std::make_shared<ByzantineDate>(outputCalendar)};

        Date posDate{byzantine->calculate(posYear)};
        REQUIRE(posDate.year == 7527);
        REQUIRE(posDate.month == 4);
        REQUIRE(posDate.day == 15);

        Date zeroDate{byzantine->calculate(zeroYear)};
        REQUIRE(zeroDate.year == 5508);
        REQUIRE(zeroDate.month == 4);
        REQUIRE(zeroDate.day == 11);

        Date negDate{byzantine->calculate(negYear)};
        REQUIRE(negDate.year == 5507);
        REQUIRE(negDate.month == 3);
        REQUIRE(negDate.day == 22);
      } // Julian Calculation - Pascha - Julian Output Calendar - B.C. Style year
    } // Julian Calculation - Pascha - Julian Output Calendar

    SECTION("Revised Julian Output Calendar")
    {
      std::shared_ptr<ICalculationMethod> outputCalendar{std::make_shared<RevisedJulianOutputCalendar>(method)};

      SECTION("A.D. Style year")
      {
        Date posDate{outputCalendar->calculate(posYear)};
        REQUIRE(posDate.year == 2019);
        REQUIRE(posDate.month == 4);
        REQUIRE(posDate.day == 28);

        Date zeroDate{outputCalendar->calculate(zeroYear)};
        REQUIRE(zeroDate.year == 0);
        REQUIRE(zeroDate.month == 4);
        REQUIRE(zeroDate.day == 9);

        Date negDate{outputCalendar->calculate(negYear)};
        REQUIRE(negDate.year == -1);
        REQUIRE(negDate.month == 3);
        REQUIRE(negDate.day == 19);
      } // Julian Calculation - Pascha - Revised Julian Output Calendar - A.D. Style year

      SECTION("Byzantine Style year")
      {
        std::shared_ptr<ICalculationMethod> byzantine{std::make_shared<ByzantineDate>(outputCalendar)};

        Date posDate{byzantine->calculate(posYear)};
        REQUIRE(posDate.year == 7527);
        REQUIRE(posDate.month == 4);
        REQUIRE(posDate.day == 28);

        Date zeroDate{byzantine->calculate(zeroYear)};
        REQUIRE(zeroDate.year == 5508);
        REQUIRE(zeroDate.month == 4);
        REQUIRE(zeroDate.day == 9);

        Date negDate{byzantine->calculate(negYear)};
        REQUIRE(negDate.year == 5507);
        REQUIRE(negDate.month == 3);
        REQUIRE(negDate.day == 19);
      } // Julian Calculation - Pascha - Revised Julian Output Calendar - B.C. Style year
    } // Julian Calculation - Pascha - Revised Julian Output Calendar
  } // Julian Calculation - Pascha

  SECTION("Meatfare")
  {
    std::shared_ptr<ICalculationMethod> targetMethod{std::make_shared<Meatfare>(method)};

    SECTION("Gregorian Output Calendar")
    {
      SECTION("A.D. Style year")
      {
        Date posDate{targetMethod->calculate(posYear)};
        REQUIRE(posDate.year == 2019);
        REQUIRE(posDate.month == 3);
        REQUIRE(posDate.day == 3);

        Date zeroDate{targetMethod->calculate(zeroYear)};
        REQUIRE(zeroDate.year == 0);
        REQUIRE(zeroDate.month == 2);
        REQUIRE(zeroDate.day == 13);

        Date negDate{targetMethod->calculate(negYear)};
        REQUIRE(negDate.year == -1);
        REQUIRE(negDate.month == 1);
        REQUIRE(negDate.day == 23);
      } // Julian Calculation - Meatfare - Gregorian Output Calendar - A.D. Style year

      SECTION("Byzantine Style year")
      {
        std::shared_ptr<ICalculationMethod> byzantine{std::make_shared<ByzantineDate>(targetMethod)};

        Date posDate{byzantine->calculate(posYear)};
        REQUIRE(posDate.year == 7527);
        REQUIRE(posDate.month == 3);
        REQUIRE(posDate.day == 3);

        Date zeroDate{byzantine->calculate(zeroYear)};
        REQUIRE(zeroDate.year == 5508);
        REQUIRE(zeroDate.month == 2);
        REQUIRE(zeroDate.day == 13);

        Date negDate{byzantine->calculate(negYear)};
        REQUIRE(negDate.year == 5507);
        REQUIRE(negDate.month == 1);
        REQUIRE(negDate.day == 23);
      } // Julian Calculation - Meatfare - Gregorian Output Calendar - B.C. Style year
    } // Julian Calculation - Meatfare - Gregorian Output Calendar
    
    SECTION("Julian Output Calendar")
    {
      std::shared_ptr<ICalculationMethod> outputCalendar{std::make_shared<JulianOutputCalendar>(targetMethod)};

      SECTION("A.D. Style year")
      {
        Date posDate{outputCalendar->calculate(posYear)};
        REQUIRE(posDate.year == 2019);
        REQUIRE(posDate.month == 2);
        REQUIRE(posDate.day == 18);

        Date zeroDate{outputCalendar->calculate(zeroYear)};
        REQUIRE(zeroDate.year == 0);
        REQUIRE(zeroDate.month == 2);
        REQUIRE(zeroDate.day == 15);

        Date negDate{outputCalendar->calculate(negYear)};
        REQUIRE(negDate.year == -1);
        REQUIRE(negDate.month == 1);
        REQUIRE(negDate.day == 25);
      } // Julian Calculation - Meatfare - Julian Output Calendar - A.D. Style year

      SECTION("Byzantine Style year")
      {
        std::shared_ptr<ICalculationMethod> byzantine{std::make_shared<ByzantineDate>(outputCalendar)};

        Date posDate{byzantine->calculate(posYear)};
        REQUIRE(posDate.year == 7527);
        REQUIRE(posDate.month == 2);
        REQUIRE(posDate.day == 18);

        Date zeroDate{byzantine->calculate(zeroYear)};
        REQUIRE(zeroDate.year == 5508);
        REQUIRE(zeroDate.month == 2);
        REQUIRE(zeroDate.day == 15);

        Date negDate{byzantine->calculate(negYear)};
        REQUIRE(negDate.year == 5507);
        REQUIRE(negDate.month == 1);
        REQUIRE(negDate.day == 25);
      } // Julian Calculation - Meatfare - Julian Output Calendar - B.C. Style year
    } // Julian Calculation - Meatfare - Julian Output Calendar

    SECTION("Revised Julian Output Calendar")
    {
      std::shared_ptr<ICalculationMethod> outputCalendar{std::make_shared<RevisedJulianOutputCalendar>(targetMethod)};

      SECTION("A.D. Style year")
      {
        Date posDate{outputCalendar->calculate(posYear)};
        REQUIRE(posDate.year == 2019);
        REQUIRE(posDate.month == 3);
        REQUIRE(posDate.day == 3);

        Date zeroDate{outputCalendar->calculate(zeroYear)};
        REQUIRE(zeroDate.year == 0);
        REQUIRE(zeroDate.month == 2);
        REQUIRE(zeroDate.day == 12);

        Date negDate{outputCalendar->calculate(negYear)};
        REQUIRE(negDate.year == -1);
        REQUIRE(negDate.month == 1);
        REQUIRE(negDate.day == 22);
      } // Julian Calculation - Meatfare - Revised Julian Output Calendar - A.D. Style year

      SECTION("Byzantine Style year")
      {
        std::shared_ptr<ICalculationMethod> byzantine{std::make_shared<ByzantineDate>(outputCalendar)};

        Date posDate{byzantine->calculate(posYear)};
        REQUIRE(posDate.year == 7527);
        REQUIRE(posDate.month == 3);
        REQUIRE(posDate.day == 3);

        Date zeroDate{byzantine->calculate(zeroYear)};
        REQUIRE(zeroDate.year == 5508);
        REQUIRE(zeroDate.month == 2);
        REQUIRE(zeroDate.day == 12);

        Date negDate{byzantine->calculate(negYear)};
        REQUIRE(negDate.year == 5507);
        REQUIRE(negDate.month == 1);
        REQUIRE(negDate.day == 22);
      } // Julian Calculation - Meatfare - Revised Julian Output Calendar - B.C. Style year
    } // Julian Calculation - Meatfare - Revised Julian Output Calendar
  } // Julian Calculation Meatfare

  SECTION("Cheesefare")
  {
    std::shared_ptr<ICalculationMethod> targetMethod{std::make_shared<Cheesefare>(method)};

    SECTION("Gregorian Output Calendar")
    {
      SECTION("A.D. Style year")
      {
        Date posDate{targetMethod->calculate(posYear)};
        REQUIRE(posDate.year == 2019);
        REQUIRE(posDate.month == 3);
        REQUIRE(posDate.day == 10);

        Date zeroDate{targetMethod->calculate(zeroYear)};
        REQUIRE(zeroDate.year == 0);
        REQUIRE(zeroDate.month == 2);
        REQUIRE(zeroDate.day == 20);

        Date negDate{targetMethod->calculate(negYear)};
        REQUIRE(negDate.year == -1);
        REQUIRE(negDate.month == 1);
        REQUIRE(negDate.day == 30);
      } // Julian Calculation - Cheesefare - Gregorian Output Calendar - A.D. Style year

      SECTION("Byzantine Style year")
      {
        std::shared_ptr<ICalculationMethod> byzantine{std::make_shared<ByzantineDate>(targetMethod)};

        Date posDate{byzantine->calculate(posYear)};
        REQUIRE(posDate.year == 7527);
        REQUIRE(posDate.month == 3);
        REQUIRE(posDate.day == 10);

        Date zeroDate{byzantine->calculate(zeroYear)};
        REQUIRE(zeroDate.year == 5508);
        REQUIRE(zeroDate.month == 2);
        REQUIRE(zeroDate.day == 20);

        Date negDate{byzantine->calculate(negYear)};
        REQUIRE(negDate.year == 5507);
        REQUIRE(negDate.month == 1);
        REQUIRE(negDate.day == 30);
      } // Julian Calculation - Cheesefare - Gregorian Output Calendar - B.C. Style year
    } // Julian Calculation - Cheesefare - Gregorian Output Calendar

    SECTION("Julian Output Calendar")
    {
      std::shared_ptr<ICalculationMethod> outputCalendar{std::make_shared<JulianOutputCalendar>(targetMethod)};

      SECTION("A.D. Style year")
      {
        Date posDate{outputCalendar->calculate(posYear)};
        REQUIRE(posDate.year == 2019);
        REQUIRE(posDate.month == 2);
        REQUIRE(posDate.day == 25);

        Date zeroDate{outputCalendar->calculate(zeroYear)};
        REQUIRE(zeroDate.year == 0);
        REQUIRE(zeroDate.month == 2);
        REQUIRE(zeroDate.day == 22);

        Date negDate{outputCalendar->calculate(negYear)};
        REQUIRE(negDate.year == -1);
        REQUIRE(negDate.month == 2);
        REQUIRE(negDate.day == 1);
      } // Julian Calculation - Cheesefare - Julian Output Calendar - A.D. Style year

      SECTION("Byzantine Style year")
      {
        std::shared_ptr<ICalculationMethod> byzantine{std::make_shared<ByzantineDate>(outputCalendar)};

        Date posDate{byzantine->calculate(posYear)};
        REQUIRE(posDate.year == 7527);
        REQUIRE(posDate.month == 2);
        REQUIRE(posDate.day == 25);

        Date zeroDate{byzantine->calculate(zeroYear)};
        REQUIRE(zeroDate.year == 5508);
        REQUIRE(zeroDate.month == 2);
        REQUIRE(zeroDate.day == 22);

        Date negDate{byzantine->calculate(negYear)};
        REQUIRE(negDate.year == 5507);
        REQUIRE(negDate.month == 2);
        REQUIRE(negDate.day == 1);
      } // Julian Calculation - Cheesefare - Julian Output Calendar - B.C. Style year
    } // Julian Calculation - Cheesefare - Julian Output Calendar

    SECTION("Revised Julian Output Calendar")
    {
      std::shared_ptr<ICalculationMethod> outputCalendar{std::make_shared<RevisedJulianOutputCalendar>(targetMethod)};

      SECTION("A.D. Style year")
      {
        Date posDate{outputCalendar->calculate(posYear)};
        REQUIRE(posDate.year == 2019);
        REQUIRE(posDate.month == 3);
        REQUIRE(posDate.day == 10);

        Date zeroDate{outputCalendar->calculate(zeroYear)};
        REQUIRE(zeroDate.year == 0);
        REQUIRE(zeroDate.month == 2);
        REQUIRE(zeroDate.day == 19);

        Date negDate{outputCalendar->calculate(negYear)};
        REQUIRE(negDate.year == -1);
        REQUIRE(negDate.month == 1);
        REQUIRE(negDate.day == 29);
      } // Julian Calculation - Cheesefare - Revised Julian Output Calendar - A.D. Style year

      SECTION("Byzantine Style year")
      {
        std::shared_ptr<ICalculationMethod> byzantine{std::make_shared<ByzantineDate>(outputCalendar)};

        Date posDate{byzantine->calculate(posYear)};
        REQUIRE(posDate.year == 7527);
        REQUIRE(posDate.month == 3);
        REQUIRE(posDate.day == 10);

        Date zeroDate{byzantine->calculate(zeroYear)};
        REQUIRE(zeroDate.year == 5508);
        REQUIRE(zeroDate.month == 2);
        REQUIRE(zeroDate.day == 19);

        Date negDate{byzantine->calculate(negYear)};
        REQUIRE(negDate.year == 5507);
        REQUIRE(negDate.month == 1);
        REQUIRE(negDate.day == 29);
      } // Julian Calculation - Cheesefare - Revised Julian Output Calendar - B.C. Style year
    } // Julian Calculation - Cheesefare - Revised Julian Output Calendar
  } // Julian Calculation Cheesefare

  SECTION("Ash Wednesday")
  {
    std::shared_ptr<ICalculationMethod> targetMethod{std::make_shared<AshWednesday>(method)};

    SECTION("Gregorian Output Calendar")
    {
      SECTION("A.D. Style year")
      {
        Date posDate{targetMethod->calculate(posYear)};
        REQUIRE(posDate.year == 2019);
        REQUIRE(posDate.month == 3);
        REQUIRE(posDate.day == 13);

        Date zeroDate{targetMethod->calculate(zeroYear)};
        REQUIRE(zeroDate.year == 0);
        REQUIRE(zeroDate.month == 2);
        REQUIRE(zeroDate.day == 23);

        Date negDate{targetMethod->calculate(negYear)};
        REQUIRE(negDate.year == -1);
        REQUIRE(negDate.month == 2);
        REQUIRE(negDate.day == 2);
      } // Julian Calculation - Ash Wednesday - Gregorian Output Calendar - A.D. Style year

      SECTION("Byzantine Style year")
      {
        std::shared_ptr<ICalculationMethod> byzantine{std::make_shared<ByzantineDate>(targetMethod)};

        Date posDate{byzantine->calculate(posYear)};
        REQUIRE(posDate.year == 7527);
        REQUIRE(posDate.month == 3);
        REQUIRE(posDate.day == 13);

        Date zeroDate{byzantine->calculate(zeroYear)};
        REQUIRE(zeroDate.year == 5508);
        REQUIRE(zeroDate.month == 2);
        REQUIRE(zeroDate.day == 23);

        Date negDate{byzantine->calculate(negYear)};
        REQUIRE(negDate.year == 5507);
        REQUIRE(negDate.month == 2);
        REQUIRE(negDate.day == 2);
      } // Julian Calculation - Ash Wednesday - Gregorian Output Calendar - B.C. Style year
    } // Julian Calculation - Ash Wednesday - Gregorian Output Calendar

    SECTION("Julian Output Calendar")
    {
      std::shared_ptr<ICalculationMethod> outputCalendar{std::make_shared<JulianOutputCalendar>(targetMethod)};

      SECTION("A.D. Style year")
      {
        Date posDate{outputCalendar->calculate(posYear)};
        REQUIRE(posDate.year == 2019);
        REQUIRE(posDate.month == 2);
        REQUIRE(posDate.day == 28);

        Date zeroDate{outputCalendar->calculate(zeroYear)};
        REQUIRE(zeroDate.year == 0);
        REQUIRE(zeroDate.month == 2);
        REQUIRE(zeroDate.day == 25);

        Date negDate{outputCalendar->calculate(negYear)};
        REQUIRE(negDate.year == -1);
        REQUIRE(negDate.month == 2);
        REQUIRE(negDate.day == 4);
      } // Julian Calculation - Ash Wednesday - Julian Output Calendar - A.D. Style year

      SECTION("Byzantine Style year")
      {
        std::shared_ptr<ICalculationMethod> byzantine{std::make_shared<ByzantineDate>(outputCalendar)};

        Date posDate{byzantine->calculate(posYear)};
        REQUIRE(posDate.year == 7527);
        REQUIRE(posDate.month == 2);
        REQUIRE(posDate.day == 28);

        Date zeroDate{byzantine->calculate(zeroYear)};
        REQUIRE(zeroDate.year == 5508);
        REQUIRE(zeroDate.month == 2);
        REQUIRE(zeroDate.day == 25);

        Date negDate{byzantine->calculate(negYear)};
        REQUIRE(negDate.year == 5507);
        REQUIRE(negDate.month == 2);
        REQUIRE(negDate.day == 4);
      } // Julian Calculation - Ash Wednesday - Julian Output Calendar - B.C. Style year
    } // Julian Calculation - Ash Wednesday - Julian Output Calendar

    SECTION("Revised Julian Output Calendar")
    {
      std::shared_ptr<ICalculationMethod> outputCalendar{std::make_shared<RevisedJulianOutputCalendar>(targetMethod)};

      SECTION("A.D. Style year")
      {
        Date posDate{outputCalendar->calculate(posYear)};
        REQUIRE(posDate.year == 2019);
        REQUIRE(posDate.month == 3);
        REQUIRE(posDate.day == 13);

        Date zeroDate{outputCalendar->calculate(zeroYear)};
        REQUIRE(zeroDate.year == 0);
        REQUIRE(zeroDate.month == 2);
        REQUIRE(zeroDate.day == 22);

        Date negDate{outputCalendar->calculate(negYear)};
        REQUIRE(negDate.year == -1);
        REQUIRE(negDate.month == 2);
        REQUIRE(negDate.day == 1);
      } // Julian Calculation - Ash Wednesday - Revised Julian Output Calendar - A.D. Style year

      SECTION("Byzantine Style year")
      {
        std::shared_ptr<ICalculationMethod> byzantine{std::make_shared<ByzantineDate>(outputCalendar)};

        Date posDate{byzantine->calculate(posYear)};
        REQUIRE(posDate.year == 7527);
        REQUIRE(posDate.month == 3);
        REQUIRE(posDate.day == 13);

        Date zeroDate{byzantine->calculate(zeroYear)};
        REQUIRE(zeroDate.year == 5508);
        REQUIRE(zeroDate.month == 2);
        REQUIRE(zeroDate.day == 22);

        Date negDate{byzantine->calculate(negYear)};
        REQUIRE(negDate.year == 5507);
        REQUIRE(negDate.month == 2);
        REQUIRE(negDate.day == 1);
      } // Julian Calculation - Ash Wednesday - Revised Julian Output Calendar - B.C. Style year
    } // Julian Calculation - Ash Wednesday - Revised Julian Output Calendar
  } // Julian Calculation - Ash Wednesday

  SECTION("Midfeast of Pentecost")
  {
    std::shared_ptr<ICalculationMethod> targetMethod{std::make_shared<MidfeastPentecost>(method)};

    SECTION("Gregorian Output Calendar")
    {
      SECTION("A.D. Style year")
      {
        Date posDate{targetMethod->calculate(posYear)};
        REQUIRE(posDate.year == 2019);
        REQUIRE(posDate.month == 5);
        REQUIRE(posDate.day == 22);

        Date zeroDate{targetMethod->calculate(zeroYear)};
        REQUIRE(zeroDate.year == 0);
        REQUIRE(zeroDate.month == 5);
        REQUIRE(zeroDate.day == 3);

        Date negDate{targetMethod->calculate(negYear)};
        REQUIRE(negDate.year == -1);
        REQUIRE(negDate.month == 4);
        REQUIRE(negDate.day == 13);
      } // Julian Calculation - Midfeast of Pentecost - Gregorian Output Calendar - A.D. Style year

      SECTION("Byzantine Style year")
      {
        std::shared_ptr<ICalculationMethod> byzantine{std::make_shared<ByzantineDate>(targetMethod)};

        Date posDate{byzantine->calculate(posYear)};
        REQUIRE(posDate.year == 7527);
        REQUIRE(posDate.month == 5);
        REQUIRE(posDate.day == 22);

        Date zeroDate{byzantine->calculate(zeroYear)};
        REQUIRE(zeroDate.year == 5508);
        REQUIRE(zeroDate.month == 5);
        REQUIRE(zeroDate.day == 3);

        Date negDate{byzantine->calculate(negYear)};
        REQUIRE(negDate.year == 5507);
        REQUIRE(negDate.month == 4);
        REQUIRE(negDate.day == 13);
      } // Julian Calculation - Midfeast of Pentecost - Gregorian Output Calendar - B.C. Style year
    } // Julian Calculation - Midfeast of Pentecost - Gregorian Output Calendar

    SECTION("Julian Output Calendar")
    {
      std::shared_ptr<ICalculationMethod> outputCalendar{std::make_shared<JulianOutputCalendar>(targetMethod)};

      SECTION("A.D. Style year")
      {
        Date posDate{outputCalendar->calculate(posYear)};
        REQUIRE(posDate.year == 2019);
        REQUIRE(posDate.month == 5);
        REQUIRE(posDate.day == 9);

        Date zeroDate{outputCalendar->calculate(zeroYear)};
        REQUIRE(zeroDate.year == 0);
        REQUIRE(zeroDate.month == 5);
        REQUIRE(zeroDate.day == 5);

        Date negDate{outputCalendar->calculate(negYear)};
        REQUIRE(negDate.year == -1);
        REQUIRE(negDate.month == 4);
        REQUIRE(negDate.day == 15);
      } // Julian Calculation - Midfeast of Pentecost - Julian Output Calendar - A.D. Style year

      SECTION("Byzantine Style year")
      {
        std::shared_ptr<ICalculationMethod> byzantine{std::make_shared<ByzantineDate>(outputCalendar)};

        Date posDate{byzantine->calculate(posYear)};
        REQUIRE(posDate.year == 7527);
        REQUIRE(posDate.month == 5);
        REQUIRE(posDate.day == 9);

        Date zeroDate{byzantine->calculate(zeroYear)};
        REQUIRE(zeroDate.year == 5508);
        REQUIRE(zeroDate.month == 5);
        REQUIRE(zeroDate.day == 5);

        Date negDate{byzantine->calculate(negYear)};
        REQUIRE(negDate.year == 5507);
        REQUIRE(negDate.month == 4);
        REQUIRE(negDate.day == 15);
      } // Julian Calculation - Midfeast of Pentecost - Julian Output Calendar - B.C. Style year
    } // Julian Calculation - Midfeast of Pentecost - Julian Output Calendar

    SECTION("Revised Julian Output Calendar")
    {
      std::shared_ptr<ICalculationMethod> outputCalendar{std::make_shared<RevisedJulianOutputCalendar>(targetMethod)};

      SECTION("A.D. Style year")
      {
        Date posDate{outputCalendar->calculate(posYear)};
        REQUIRE(posDate.year == 2019);
        REQUIRE(posDate.month == 5);
        REQUIRE(posDate.day == 22);

        Date zeroDate{outputCalendar->calculate(zeroYear)};
        REQUIRE(zeroDate.year == 0);
        REQUIRE(zeroDate.month == 5);
        REQUIRE(zeroDate.day == 3);

        Date negDate{outputCalendar->calculate(negYear)};
        REQUIRE(negDate.year == -1);
        REQUIRE(negDate.month == 4);
        REQUIRE(negDate.day == 12);
      } // Julian Calculation - Midfeast of Pentecost - Revised Julian Output Calendar - A.D. Style year

      SECTION("Byzantine Style year")
      {
        std::shared_ptr<ICalculationMethod> byzantine{std::make_shared<ByzantineDate>(outputCalendar)};

        Date posDate{byzantine->calculate(posYear)};
        REQUIRE(posDate.year == 7527);
        REQUIRE(posDate.month == 5);
        REQUIRE(posDate.day == 22);

        Date zeroDate{byzantine->calculate(zeroYear)};
        REQUIRE(zeroDate.year == 5508);
        REQUIRE(zeroDate.month == 5);
        REQUIRE(zeroDate.day == 3);

        Date negDate{byzantine->calculate(negYear)};
        REQUIRE(negDate.year == 5507);
        REQUIRE(negDate.month == 4);
        REQUIRE(negDate.day == 12);
      } // Julian Calculation - Midfeast of Pentecost - Revised Julian Output Calendar - B.C. Style year
    } // Julian Calculation - Midfeast of Pentecost - Revised Julian Output Calendar
  } // Julian Calculation - Midfeast of Pentecost

  SECTION("Leavetaking of Pascha")
  {
    std::shared_ptr<ICalculationMethod> targetMethod{std::make_shared<LeavetakingPascha>(method)};

    SECTION("Gregorian Output Calendar")
    {
      SECTION("A.D. Style year")
      {
        Date posDate{targetMethod->calculate(posYear)};
        REQUIRE(posDate.year == 2019);
        REQUIRE(posDate.month == 6);
        REQUIRE(posDate.day == 5);

        Date zeroDate{targetMethod->calculate(zeroYear)};
        REQUIRE(zeroDate.year == 0);
        REQUIRE(zeroDate.month == 5);
        REQUIRE(zeroDate.day == 17);

        Date negDate{targetMethod->calculate(negYear)};
        REQUIRE(negDate.year == -1);
        REQUIRE(negDate.month == 4);
        REQUIRE(negDate.day == 27);
      } // Julian Calculation - Leavetaking of Pascha - Gregorian Output Calendar - A.D. Style year

      SECTION("Byzantine Style year")
      {
        std::shared_ptr<ICalculationMethod> byzantine{std::make_shared<ByzantineDate>(targetMethod)};

        Date posDate{byzantine->calculate(posYear)};
        REQUIRE(posDate.year == 7527);
        REQUIRE(posDate.month == 6);
        REQUIRE(posDate.day == 5);

        Date zeroDate{byzantine->calculate(zeroYear)};
        REQUIRE(zeroDate.year == 5508);
        REQUIRE(zeroDate.month == 5);
        REQUIRE(zeroDate.day == 17);

        Date negDate{byzantine->calculate(negYear)};
        REQUIRE(negDate.year == 5507);
        REQUIRE(negDate.month == 4);
        REQUIRE(negDate.day == 27);
      } // Julian Calculation - Leavetaking of Pascha - Gregorian Output Calendar - B.C. Style year
    } // Julian Calculation - Leavetaking of Pascha - Gregorian Output Calendar

    SECTION("Julian Output Calendar")
    {
      std::shared_ptr<ICalculationMethod> outputCalendar{std::make_shared<JulianOutputCalendar>(targetMethod)};

      SECTION("A.D. Style year")
      {
        Date posDate{outputCalendar->calculate(posYear)};
        REQUIRE(posDate.year == 2019);
        REQUIRE(posDate.month == 5);
        REQUIRE(posDate.day == 23);

        Date zeroDate{outputCalendar->calculate(zeroYear)};
        REQUIRE(zeroDate.year == 0);
        REQUIRE(zeroDate.month == 5);
        REQUIRE(zeroDate.day == 19);

        Date negDate{outputCalendar->calculate(negYear)};
        REQUIRE(negDate.year == -1);
        REQUIRE(negDate.month == 4);
        REQUIRE(negDate.day == 29);
      } // Julian Calculation - Leavetaking of Pascha - Julian Output Calendar - A.D. Style year

      SECTION("Byzantine Style year")
      {
        std::shared_ptr<ICalculationMethod> byzantine{std::make_shared<ByzantineDate>(outputCalendar)};

        Date posDate{byzantine->calculate(posYear)};
        REQUIRE(posDate.year == 7527);
        REQUIRE(posDate.month == 5);
        REQUIRE(posDate.day == 23);

        Date zeroDate{byzantine->calculate(zeroYear)};
        REQUIRE(zeroDate.year == 5508);
        REQUIRE(zeroDate.month == 5);
        REQUIRE(zeroDate.day == 19);

        Date negDate{byzantine->calculate(negYear)};
        REQUIRE(negDate.year == 5507);
        REQUIRE(negDate.month == 4);
        REQUIRE(negDate.day == 29);
      } // Julian Calculation - Leavetaking of Pascha - Julian Output Calendar - B.C. Style year
    } // Julian Calculation - Leavetaking of Pascha - Julian Output Calendar

    SECTION("Revised Julian Output Calendar")
    {
      std::shared_ptr<ICalculationMethod> outputCalendar{std::make_shared<RevisedJulianOutputCalendar>(targetMethod)};

      SECTION("A.D. Style year")
      {
        Date posDate{outputCalendar->calculate(posYear)};
        REQUIRE(posDate.year == 2019);
        REQUIRE(posDate.month == 6);
        REQUIRE(posDate.day == 5);

        Date zeroDate{outputCalendar->calculate(zeroYear)};
        REQUIRE(zeroDate.year == 0);
        REQUIRE(zeroDate.month == 5);
        REQUIRE(zeroDate.day == 17);

        Date negDate{outputCalendar->calculate(negYear)};
        REQUIRE(negDate.year == -1);
        REQUIRE(negDate.month == 4);
        REQUIRE(negDate.day == 26);
      } // Julian Calculation - Leavetaking of Pascha - Revised Julian Output Calendar - A.D. Style year

      SECTION("Byzantine Style year")
      {
        std::shared_ptr<ICalculationMethod> byzantine{std::make_shared<ByzantineDate>(outputCalendar)};

        Date posDate{byzantine->calculate(posYear)};
        REQUIRE(posDate.year == 7527);
        REQUIRE(posDate.month == 6);
        REQUIRE(posDate.day == 5);

        Date zeroDate{byzantine->calculate(zeroYear)};
        REQUIRE(zeroDate.year == 5508);
        REQUIRE(zeroDate.month == 5);
        REQUIRE(zeroDate.day == 17);

        Date negDate{byzantine->calculate(negYear)};
        REQUIRE(negDate.year == 5507);
        REQUIRE(negDate.month == 4);
        REQUIRE(negDate.day == 26);
      } // Julian Calculation - Leavetaking of Pascha - Revised Julian Output Calendar - B.C. Style year
    } // Julian Calculation - Leavetaking of Pascha - Revised Julian Output Calendar
  } // Julian Calculation - Leavetaking of Pascha

  SECTION("Ascension")
  {
    std::shared_ptr<ICalculationMethod> targetMethod{std::make_shared<Ascension>(method)};

    SECTION("Gregorian Output Calendar")
    {
      SECTION("A.D. Style year")
      {
        Date posDate{targetMethod->calculate(posYear)};
        REQUIRE(posDate.year == 2019);
        REQUIRE(posDate.month == 6);
        REQUIRE(posDate.day == 6);

        Date zeroDate{targetMethod->calculate(zeroYear)};
        REQUIRE(zeroDate.year == 0);
        REQUIRE(zeroDate.month == 5);
        REQUIRE(zeroDate.day == 18);

        Date negDate{targetMethod->calculate(negYear)};
        REQUIRE(negDate.year == -1);
        REQUIRE(negDate.month == 4);
        REQUIRE(negDate.day == 28);
      } // Julian Calculation - Ascension - Gregorian Output Calendar - A.D. Style year

      SECTION("Byzantine Style year")
      {
        std::shared_ptr<ICalculationMethod> byzantine{std::make_shared<ByzantineDate>(targetMethod)};

        Date posDate{byzantine->calculate(posYear)};
        REQUIRE(posDate.year == 7527);
        REQUIRE(posDate.month == 6);
        REQUIRE(posDate.day == 6);

        Date zeroDate{byzantine->calculate(zeroYear)};
        REQUIRE(zeroDate.year == 5508);
        REQUIRE(zeroDate.month == 5);
        REQUIRE(zeroDate.day == 18);

        Date negDate{byzantine->calculate(negYear)};
        REQUIRE(negDate.year == 5507);
        REQUIRE(negDate.month == 4);
        REQUIRE(negDate.day == 28);
      } // Julian Calculation - Ascension - Gregorian Output Calendar - B.C. Style year
    } // Julian Calculation - Ascension - Gregorian Output Calendar

    SECTION("Julian Output Calendar")
    {
      std::shared_ptr<ICalculationMethod> outputCalendar{std::make_shared<JulianOutputCalendar>(targetMethod)};

      SECTION("A.D. Style year")
      {
        Date posDate{outputCalendar->calculate(posYear)};
        REQUIRE(posDate.year == 2019);
        REQUIRE(posDate.month == 5);
        REQUIRE(posDate.day == 24);

        Date zeroDate{outputCalendar->calculate(zeroYear)};
        REQUIRE(zeroDate.year == 0);
        REQUIRE(zeroDate.month == 5);
        REQUIRE(zeroDate.day == 20);

        Date negDate{outputCalendar->calculate(negYear)};
        REQUIRE(negDate.year == -1);
        REQUIRE(negDate.month == 4);
        REQUIRE(negDate.day == 30);
      } // Julian Calculation - Ascension - Julian Output Calendar - A.D. Style year

      SECTION("Byzantine Style year")
      {
        std::shared_ptr<ICalculationMethod> byzantine{std::make_shared<ByzantineDate>(outputCalendar)};

        Date posDate{byzantine->calculate(posYear)};
        REQUIRE(posDate.year == 7527);
        REQUIRE(posDate.month == 5);
        REQUIRE(posDate.day == 24);

        Date zeroDate{byzantine->calculate(zeroYear)};
        REQUIRE(zeroDate.year == 5508);
        REQUIRE(zeroDate.month == 5);
        REQUIRE(zeroDate.day == 20);

        Date negDate{byzantine->calculate(negYear)};
        REQUIRE(negDate.year == 5507);
        REQUIRE(negDate.month == 4);
        REQUIRE(negDate.day == 30);
      } // Julian Calculation - Ascension - Julian Output Calendar - B.C. Style year
    } // Julian Calculation - Ascension - Julian Output Calendar

    SECTION("Revised Julian Output Calendar")
    {
      std::shared_ptr<ICalculationMethod> outputCalendar{std::make_shared<RevisedJulianOutputCalendar>(targetMethod)};

      SECTION("A.D. Style year")
      {
        Date posDate{outputCalendar->calculate(posYear)};
        REQUIRE(posDate.year == 2019);
        REQUIRE(posDate.month == 6);
        REQUIRE(posDate.day == 6);

        Date zeroDate{outputCalendar->calculate(zeroYear)};
        REQUIRE(zeroDate.year == 0);
        REQUIRE(zeroDate.month == 5);
        REQUIRE(zeroDate.day == 18);

        Date negDate{outputCalendar->calculate(negYear)};
        REQUIRE(negDate.year == -1);
        REQUIRE(negDate.month == 4);
        REQUIRE(negDate.day == 27);
      } // Julian Calculation - Ascension - Revised Julian Output Calendar - A.D. Style year

      SECTION("Byzantine Style year")
      {
        std::shared_ptr<ICalculationMethod> byzantine{std::make_shared<ByzantineDate>(outputCalendar)};

        Date posDate{byzantine->calculate(posYear)};
        REQUIRE(posDate.year == 7527);
        REQUIRE(posDate.month == 6);
        REQUIRE(posDate.day == 6);

        Date zeroDate{byzantine->calculate(zeroYear)};
        REQUIRE(zeroDate.year == 5508);
        REQUIRE(zeroDate.month == 5);
        REQUIRE(zeroDate.day == 18);

        Date negDate{byzantine->calculate(negYear)};
        REQUIRE(negDate.year == 5507);
        REQUIRE(negDate.month == 4);
        REQUIRE(negDate.day == 27);
      } // Julian Calculation - Ascension - Revised Julian Output Calendar - B.C. Style year
    } // Julian Calculation - Ascension - Revised Julian Output Calendar
  } // Julian Calculation - Ascension

  SECTION("Pentecost")
  {
    std::shared_ptr<ICalculationMethod> targetMethod{std::make_shared<Pentecost>(method)};

    SECTION("Gregorian Output Calendar")
    {
      SECTION("A.D. Style year")
      {
        Date posDate{targetMethod->calculate(posYear)};
        REQUIRE(posDate.year == 2019);
        REQUIRE(posDate.month == 6);
        REQUIRE(posDate.day == 16);

        Date zeroDate{targetMethod->calculate(zeroYear)};
        REQUIRE(zeroDate.year == 0);
        REQUIRE(zeroDate.month == 5);
        REQUIRE(zeroDate.day == 28);

        Date negDate{targetMethod->calculate(negYear)};
        REQUIRE(negDate.year == -1);
        REQUIRE(negDate.month == 5);
        REQUIRE(negDate.day == 8);
      } // Julian Calculation - Pentecost - Gregorian Output Calendar - A.D. Style year

      SECTION("Byzantine Style year")
      {
        std::shared_ptr<ICalculationMethod> byzantine{std::make_shared<ByzantineDate>(targetMethod)};

        Date posDate{byzantine->calculate(posYear)};
        REQUIRE(posDate.year == 7527);
        REQUIRE(posDate.month == 6);
        REQUIRE(posDate.day == 16);

        Date zeroDate{byzantine->calculate(zeroYear)};
        REQUIRE(zeroDate.year == 5508);
        REQUIRE(zeroDate.month == 5);
        REQUIRE(zeroDate.day == 28);

        Date negDate{byzantine->calculate(negYear)};
        REQUIRE(negDate.year == 5507);
        REQUIRE(negDate.month == 5);
        REQUIRE(negDate.day == 8);
      } // Julian Calculation - Pentecost - Gregorian Output Calendar - B.C. Style year
    } // Julian Calculation - Pentecost - Gregorian Output Calendar

    SECTION("Julian Output Calendar")
    {
      std::shared_ptr<ICalculationMethod> outputCalendar{std::make_shared<JulianOutputCalendar>(targetMethod)};

      SECTION("A.D. Style year")
      {
        Date posDate{outputCalendar->calculate(posYear)};
        REQUIRE(posDate.year == 2019);
        REQUIRE(posDate.month == 6);
        REQUIRE(posDate.day == 3);

        Date zeroDate{outputCalendar->calculate(zeroYear)};
        REQUIRE(zeroDate.year == 0);
        REQUIRE(zeroDate.month == 5);
        REQUIRE(zeroDate.day == 30);

        Date negDate{outputCalendar->calculate(negYear)};
        REQUIRE(negDate.year == -1);
        REQUIRE(negDate.month == 5);
        REQUIRE(negDate.day == 10);
      } // Julian Calculation - Pentecost - Julian Output Calendar - A.D. Style year

      SECTION("Byzantine Style year")
      {
        std::shared_ptr<ICalculationMethod> byzantine{std::make_shared<ByzantineDate>(outputCalendar)};

        Date posDate{byzantine->calculate(posYear)};
        REQUIRE(posDate.year == 7527);
        REQUIRE(posDate.month == 6);
        REQUIRE(posDate.day == 3);

        Date zeroDate{byzantine->calculate(zeroYear)};
        REQUIRE(zeroDate.year == 5508);
        REQUIRE(zeroDate.month == 5);
        REQUIRE(zeroDate.day == 30);

        Date negDate{byzantine->calculate(negYear)};
        REQUIRE(negDate.year == 5507);
        REQUIRE(negDate.month == 5);
        REQUIRE(negDate.day == 10);
      } // Julian Calculation - Pentecost - Julian Output Calendar - B.C. Style year
    } // Julian Calculation - Pentecost - Julian Output Calendar

    SECTION("Revised Julian Output Calendar")
    {
      std::shared_ptr<ICalculationMethod> outputCalendar{std::make_shared<RevisedJulianOutputCalendar>(targetMethod)};

      SECTION("A.D. Style year")
      {
        Date posDate{outputCalendar->calculate(posYear)};
        REQUIRE(posDate.year == 2019);
        REQUIRE(posDate.month == 6);
        REQUIRE(posDate.day == 16);

        Date zeroDate{outputCalendar->calculate(zeroYear)};
        REQUIRE(zeroDate.year == 0);
        REQUIRE(zeroDate.month == 5);
        REQUIRE(zeroDate.day == 28);

        Date negDate{outputCalendar->calculate(negYear)};
        REQUIRE(negDate.year == -1);
        REQUIRE(negDate.month == 5);
        REQUIRE(negDate.day == 7);
      } // Julian Calculation - Pentecost - Revised Julian Output Calendar - A.D. Style year

      SECTION("Byzantine Style year")
      {
        std::shared_ptr<ICalculationMethod> byzantine{std::make_shared<ByzantineDate>(outputCalendar)};

        Date posDate{byzantine->calculate(posYear)};
        REQUIRE(posDate.year == 7527);
        REQUIRE(posDate.month == 6);
        REQUIRE(posDate.day == 16);

        Date zeroDate{byzantine->calculate(zeroYear)};
        REQUIRE(zeroDate.year == 5508);
        REQUIRE(zeroDate.month == 5);
        REQUIRE(zeroDate.day == 28);

        Date negDate{byzantine->calculate(negYear)};
        REQUIRE(negDate.year == 5507);
        REQUIRE(negDate.month == 5);
        REQUIRE(negDate.day == 7);
      } // Julian Calculation - Pentecost - Revised Julian Output Calendar - B.C. Style year
    } // Julian Calculation - Pentecost - Revised Julian Output Calendar
  } // Julian Calculation - Pentecost
} // Julian Calculation

TEST_CASE("Gregorian Calculation")
{
  using namespace pascha;

  Year posYear{2019};
  Year zeroYear{0};
  Year negYear{-1};

  std::shared_ptr<pascha::ICalculationMethod> method{std::make_shared<GregorianCalculationMethod>()};

  SECTION("Pascha")
  {
    SECTION("Gregorian Output Calendar")
    {
      SECTION("A.D. Style year")
      {
        Date posDate{method->calculate(posYear)};
        REQUIRE(posDate.year == 2019);
        REQUIRE(posDate.month == 4);
        REQUIRE(posDate.day == 21);

        Date zeroDate{method->calculate(zeroYear)};
        REQUIRE(zeroDate.year == 0);
        REQUIRE(zeroDate.month == 4);
        REQUIRE(zeroDate.day == 9);

        Date negDate{method->calculate(negYear)};
        REQUIRE(negDate.year == -1);
        REQUIRE(negDate.month == 3);
        REQUIRE(negDate.day == 20);
      } // Gregorian Calculation - Pascha - Gregorian Output Calendar - A.D. Style year

      SECTION("Byzantine Style year")
      {
        std::shared_ptr<ICalculationMethod> byzantine{std::make_shared<ByzantineDate>(method)};

        Date posDate{byzantine->calculate(posYear)};
        REQUIRE(posDate.year == 7527);
        REQUIRE(posDate.month == 4);
        REQUIRE(posDate.day == 21);

        Date zeroDate{byzantine->calculate(zeroYear)};
        REQUIRE(zeroDate.year == 5508);
        REQUIRE(zeroDate.month == 4);
        REQUIRE(zeroDate.day == 9);

        Date negDate{byzantine->calculate(negYear)};
        REQUIRE(negDate.year == 5507);
        REQUIRE(negDate.month == 3);
        REQUIRE(negDate.day == 20);
      } // Gregorian Calculation - Pascha - Gregorian Output Calendar - B.C. Style year
    } // Gregorian Calculation - Pascha - Gregorian Output Calendar

    SECTION("Julian Output Calendar")
    {
      std::shared_ptr<ICalculationMethod> outputCalendar{std::make_shared<JulianOutputCalendar>(method)};

      SECTION("A.D. Style year")
      {
        Date posDate{outputCalendar->calculate(posYear)};
        REQUIRE(posDate.year == 2019);
        REQUIRE(posDate.month == 4);
        REQUIRE(posDate.day == 8);

        Date zeroDate{outputCalendar->calculate(zeroYear)};
        REQUIRE(zeroDate.year == 0);
        REQUIRE(zeroDate.month == 4);
        REQUIRE(zeroDate.day == 11);

        Date negDate{outputCalendar->calculate(negYear)};
        REQUIRE(negDate.year == -1);
        REQUIRE(negDate.month == 3);
        REQUIRE(negDate.day == 22);
      } // Gregorian Calculation - Pascha - Julian Output Calendar - A.D. Style year

      SECTION("Byzantine Style year")
      {
        std::shared_ptr<ICalculationMethod> byzantine{std::make_shared<ByzantineDate>(outputCalendar)};

        Date posDate{byzantine->calculate(posYear)};
        REQUIRE(posDate.year == 7527);
        REQUIRE(posDate.month == 4);
        REQUIRE(posDate.day == 8);

        Date zeroDate{byzantine->calculate(zeroYear)};
        REQUIRE(zeroDate.year == 5508);
        REQUIRE(zeroDate.month == 4);
        REQUIRE(zeroDate.day == 11);

        Date negDate{byzantine->calculate(negYear)};
        REQUIRE(negDate.year == 5507);
        REQUIRE(negDate.month == 3);
        REQUIRE(negDate.day == 22);
      } // Gregorian Calculation - Pascha - Julian Output Calendar - B.C. Style year
    } // Gregorian Calculation - Pascha - Julian Output Calendar

    SECTION("Revised Julian Output Calendar")
    {
      std::shared_ptr<ICalculationMethod> outputCalendar{std::make_shared<RevisedJulianOutputCalendar>(method)};

      SECTION("A.D. Style year")
      {
        Date posDate{outputCalendar->calculate(posYear)};
        REQUIRE(posDate.year == 2019);
        REQUIRE(posDate.month == 4);
        REQUIRE(posDate.day == 21);

        Date zeroDate{outputCalendar->calculate(zeroYear)};
        REQUIRE(zeroDate.year == 0);
        REQUIRE(zeroDate.month == 4);
        REQUIRE(zeroDate.day == 9);

        Date negDate{outputCalendar->calculate(negYear)};
        REQUIRE(negDate.year == -1);
        REQUIRE(negDate.month == 3);
        REQUIRE(negDate.day == 19);
      } // Gregorian Calculation - Pascha - Revised Julian Output Calendar - A.D. Style year

      SECTION("Byzantine Style year")
      {
        std::shared_ptr<ICalculationMethod> byzantine{std::make_shared<ByzantineDate>(outputCalendar)};

        Date posDate{byzantine->calculate(posYear)};
        REQUIRE(posDate.year == 7527);
        REQUIRE(posDate.month == 4);
        REQUIRE(posDate.day == 21);

        Date zeroDate{byzantine->calculate(zeroYear)};
        REQUIRE(zeroDate.year == 5508);
        REQUIRE(zeroDate.month == 4);
        REQUIRE(zeroDate.day == 9);

        Date negDate{byzantine->calculate(negYear)};
        REQUIRE(negDate.year == 5507);
        REQUIRE(negDate.month == 3);
        REQUIRE(negDate.day == 19);
      } // Gregorian Calculation - Pascha - Revised Julian Output Calendar - B.C. Style year
    } // Gregorian Calculation - Pascha - Revised Julian Output Calendar
  } // Gregorian Calculation - Pascha

  SECTION("Meatfare")
  {
    std::shared_ptr<ICalculationMethod> targetMethod{std::make_shared<Meatfare>(method)};

    SECTION("Gregorian Output Calendar")
    {
      SECTION("A.D. Style year")
      {
        Date posDate{targetMethod->calculate(posYear)};
        REQUIRE(posDate.year == 2019);
        REQUIRE(posDate.month == 2);
        REQUIRE(posDate.day == 24);

        Date zeroDate{targetMethod->calculate(zeroYear)};
        REQUIRE(zeroDate.year == 0);
        REQUIRE(zeroDate.month == 2);
        REQUIRE(zeroDate.day == 13);

        Date negDate{targetMethod->calculate(negYear)};
        REQUIRE(negDate.year == -1);
        REQUIRE(negDate.month == 1);
        REQUIRE(negDate.day == 23);
      } // Gregorian Calculation - Meatfare - Gregorian Output Calendar - A.D. Style year

      SECTION("Byzantine Style year")
      {
        std::shared_ptr<ICalculationMethod> byzantine{std::make_shared<ByzantineDate>(targetMethod)};

        Date posDate{byzantine->calculate(posYear)};
        REQUIRE(posDate.year == 7527);
        REQUIRE(posDate.month == 2);
        REQUIRE(posDate.day == 24);

        Date zeroDate{byzantine->calculate(zeroYear)};
        REQUIRE(zeroDate.year == 5508);
        REQUIRE(zeroDate.month == 2);
        REQUIRE(zeroDate.day == 13);

        Date negDate{byzantine->calculate(negYear)};
        REQUIRE(negDate.year == 5507);
        REQUIRE(negDate.month == 1);
        REQUIRE(negDate.day == 23);
      } // Gregorian Calculation - Meatfare - Gregorian Output Calendar - B.C. Style year
    } // Gregorian Calculation - Meatfare - Gregorian Output Calendar
    
    SECTION("Julian Output Calendar")
    {
      std::shared_ptr<ICalculationMethod> outputCalendar{std::make_shared<JulianOutputCalendar>(targetMethod)};

      SECTION("A.D. Style year")
      {
        Date posDate{outputCalendar->calculate(posYear)};
        REQUIRE(posDate.year == 2019);
        REQUIRE(posDate.month == 2);
        REQUIRE(posDate.day == 11);

        Date zeroDate{outputCalendar->calculate(zeroYear)};
        REQUIRE(zeroDate.year == 0);
        REQUIRE(zeroDate.month == 2);
        REQUIRE(zeroDate.day == 15);

        Date negDate{outputCalendar->calculate(negYear)};
        REQUIRE(negDate.year == -1);
        REQUIRE(negDate.month == 1);
        REQUIRE(negDate.day == 25);
      } // Gregorian Calculation - Meatfare - Julian Output Calendar - A.D. Style year

      SECTION("Byzantine Style year")
      {
        std::shared_ptr<ICalculationMethod> byzantine{std::make_shared<ByzantineDate>(outputCalendar)};

        Date posDate{byzantine->calculate(posYear)};
        REQUIRE(posDate.year == 7527);
        REQUIRE(posDate.month == 2);
        REQUIRE(posDate.day == 11);

        Date zeroDate{byzantine->calculate(zeroYear)};
        REQUIRE(zeroDate.year == 5508);
        REQUIRE(zeroDate.month == 2);
        REQUIRE(zeroDate.day == 15);

        Date negDate{byzantine->calculate(negYear)};
        REQUIRE(negDate.year == 5507);
        REQUIRE(negDate.month == 1);
        REQUIRE(negDate.day == 25);
      } // Gregorian Calculation - Meatfare - Julian Output Calendar - B.C. Style year
    } // Gregorian Calculation - Meatfare - Julian Output Calendar

    SECTION("Revised Julian Output Calendar")
    {
      std::shared_ptr<ICalculationMethod> outputCalendar{std::make_shared<RevisedJulianOutputCalendar>(targetMethod)};

      SECTION("A.D. Style year")
      {
        Date posDate{outputCalendar->calculate(posYear)};
        REQUIRE(posDate.year == 2019);
        REQUIRE(posDate.month == 2);
        REQUIRE(posDate.day == 24);

        Date zeroDate{outputCalendar->calculate(zeroYear)};
        REQUIRE(zeroDate.year == 0);
        REQUIRE(zeroDate.month == 2);
        REQUIRE(zeroDate.day == 12);

        Date negDate{outputCalendar->calculate(negYear)};
        REQUIRE(negDate.year == -1);
        REQUIRE(negDate.month == 1);
        REQUIRE(negDate.day == 22);
      } // Gregorian Calculation - Meatfare - Revised Julian Output Calendar - A.D. Style year

      SECTION("Byzantine Style year")
      {
        std::shared_ptr<ICalculationMethod> byzantine{std::make_shared<ByzantineDate>(outputCalendar)};

        Date posDate{byzantine->calculate(posYear)};
        REQUIRE(posDate.year == 7527);
        REQUIRE(posDate.month == 2);
        REQUIRE(posDate.day == 24);

        Date zeroDate{byzantine->calculate(zeroYear)};
        REQUIRE(zeroDate.year == 5508);
        REQUIRE(zeroDate.month == 2);
        REQUIRE(zeroDate.day == 12);

        Date negDate{byzantine->calculate(negYear)};
        REQUIRE(negDate.year == 5507);
        REQUIRE(negDate.month == 1);
        REQUIRE(negDate.day == 22);
      } // Gregorian Calculation - Meatfare - Revised Julian Output Calendar - B.C. Style year
    } // Gregorian Calculation - Meatfare - Revised Julian Output Calendar
  } // Gregorian Calculation Meatfare

  SECTION("Cheesefare")
  {
    std::shared_ptr<ICalculationMethod> targetMethod{std::make_shared<Cheesefare>(method)};

    SECTION("Gregorian Output Calendar")
    {
      SECTION("A.D. Style year")
      {
        Date posDate{targetMethod->calculate(posYear)};
        REQUIRE(posDate.year == 2019);
        REQUIRE(posDate.month == 3);
        REQUIRE(posDate.day == 3);

        Date zeroDate{targetMethod->calculate(zeroYear)};
        REQUIRE(zeroDate.year == 0);
        REQUIRE(zeroDate.month == 2);
        REQUIRE(zeroDate.day == 20);

        Date negDate{targetMethod->calculate(negYear)};
        REQUIRE(negDate.year == -1);
        REQUIRE(negDate.month == 1);
        REQUIRE(negDate.day == 30);
      } // Gregorian Calculation - Cheesefare - Gregorian Output Calendar - A.D. Style year

      SECTION("Byzantine Style year")
      {
        std::shared_ptr<ICalculationMethod> byzantine{std::make_shared<ByzantineDate>(targetMethod)};

        Date posDate{byzantine->calculate(posYear)};
        REQUIRE(posDate.year == 7527);
        REQUIRE(posDate.month == 3);
        REQUIRE(posDate.day == 3);

        Date zeroDate{byzantine->calculate(zeroYear)};
        REQUIRE(zeroDate.year == 5508);
        REQUIRE(zeroDate.month == 2);
        REQUIRE(zeroDate.day == 20);

        Date negDate{byzantine->calculate(negYear)};
        REQUIRE(negDate.year == 5507);
        REQUIRE(negDate.month == 1);
        REQUIRE(negDate.day == 30);
      } // Gregorian Calculation - Cheesefare - Gregorian Output Calendar - B.C. Style year
    } // Gregorian Calculation - Cheesefare - Gregorian Output Calendar

    SECTION("Julian Output Calendar")
    {
      std::shared_ptr<ICalculationMethod> outputCalendar{std::make_shared<JulianOutputCalendar>(targetMethod)};

      SECTION("A.D. Style year")
      {
        Date posDate{outputCalendar->calculate(posYear)};
        REQUIRE(posDate.year == 2019);
        REQUIRE(posDate.month == 2);
        REQUIRE(posDate.day == 18);

        Date zeroDate{outputCalendar->calculate(zeroYear)};
        REQUIRE(zeroDate.year == 0);
        REQUIRE(zeroDate.month == 2);
        REQUIRE(zeroDate.day == 22);

        Date negDate{outputCalendar->calculate(negYear)};
        REQUIRE(negDate.year == -1);
        REQUIRE(negDate.month == 2);
        REQUIRE(negDate.day == 1);
      } // Gregorian Calculation - Cheesefare - Julian Output Calendar - A.D. Style year

      SECTION("Byzantine Style year")
      {
        std::shared_ptr<ICalculationMethod> byzantine{std::make_shared<ByzantineDate>(outputCalendar)};

        Date posDate{byzantine->calculate(posYear)};
        REQUIRE(posDate.year == 7527);
        REQUIRE(posDate.month == 2);
        REQUIRE(posDate.day == 18);

        Date zeroDate{byzantine->calculate(zeroYear)};
        REQUIRE(zeroDate.year == 5508);
        REQUIRE(zeroDate.month == 2);
        REQUIRE(zeroDate.day == 22);

        Date negDate{byzantine->calculate(negYear)};
        REQUIRE(negDate.year == 5507);
        REQUIRE(negDate.month == 2);
        REQUIRE(negDate.day == 1);
      } // Gregorian Calculation - Cheesefare - Julian Output Calendar - B.C. Style year
    } // Gregorian Calculation - Cheesefare - Julian Output Calendar

    SECTION("Revised Julian Output Calendar")
    {
      std::shared_ptr<ICalculationMethod> outputCalendar{std::make_shared<RevisedJulianOutputCalendar>(targetMethod)};

      SECTION("A.D. Style year")
      {
        Date posDate{outputCalendar->calculate(posYear)};
        REQUIRE(posDate.year == 2019);
        REQUIRE(posDate.month == 3);
        REQUIRE(posDate.day == 3);

        Date zeroDate{outputCalendar->calculate(zeroYear)};
        REQUIRE(zeroDate.year == 0);
        REQUIRE(zeroDate.month == 2);
        REQUIRE(zeroDate.day == 19);

        Date negDate{outputCalendar->calculate(negYear)};
        REQUIRE(negDate.year == -1);
        REQUIRE(negDate.month == 1);
        REQUIRE(negDate.day == 29);
      } // Gregorian Calculation - Cheesefare - Revised Julian Output Calendar - A.D. Style year

      SECTION("Byzantine Style year")
      {
        std::shared_ptr<ICalculationMethod> byzantine{std::make_shared<ByzantineDate>(outputCalendar)};

        Date posDate{byzantine->calculate(posYear)};
        REQUIRE(posDate.year == 7527);
        REQUIRE(posDate.month == 3);
        REQUIRE(posDate.day == 3);

        Date zeroDate{byzantine->calculate(zeroYear)};
        REQUIRE(zeroDate.year == 5508);
        REQUIRE(zeroDate.month == 2);
        REQUIRE(zeroDate.day == 19);

        Date negDate{byzantine->calculate(negYear)};
        REQUIRE(negDate.year == 5507);
        REQUIRE(negDate.month == 1);
        REQUIRE(negDate.day == 29);
      } // Gregorian Calculation - Cheesefare - Revised Julian Output Calendar - B.C. Style year
    } // Gregorian Calculation - Cheesefare - Revised Julian Output Calendar
  } // Gregorian Calculation Cheesefare

  SECTION("Ash Wednesday")
  {
    std::shared_ptr<ICalculationMethod> targetMethod{std::make_shared<AshWednesday>(method)};

    SECTION("Gregorian Output Calendar")
    {
      SECTION("A.D. Style year")
      {
        Date posDate{targetMethod->calculate(posYear)};
        REQUIRE(posDate.year == 2019);
        REQUIRE(posDate.month == 3);
        REQUIRE(posDate.day == 6);

        Date zeroDate{targetMethod->calculate(zeroYear)};
        REQUIRE(zeroDate.year == 0);
        REQUIRE(zeroDate.month == 2);
        REQUIRE(zeroDate.day == 23);

        Date negDate{targetMethod->calculate(negYear)};
        REQUIRE(negDate.year == -1);
        REQUIRE(negDate.month == 2);
        REQUIRE(negDate.day == 2);
      } // Gregorian Calculation - Ash Wednesday - Gregorian Output Calendar - A.D. Style year

      SECTION("Byzantine Style year")
      {
        std::shared_ptr<ICalculationMethod> byzantine{std::make_shared<ByzantineDate>(targetMethod)};

        Date posDate{byzantine->calculate(posYear)};
        REQUIRE(posDate.year == 7527);
        REQUIRE(posDate.month == 3);
        REQUIRE(posDate.day == 6);

        Date zeroDate{byzantine->calculate(zeroYear)};
        REQUIRE(zeroDate.year == 5508);
        REQUIRE(zeroDate.month == 2);
        REQUIRE(zeroDate.day == 23);

        Date negDate{byzantine->calculate(negYear)};
        REQUIRE(negDate.year == 5507);
        REQUIRE(negDate.month == 2);
        REQUIRE(negDate.day == 2);
      } // Gregorian Calculation - Ash Wednesday - Gregorian Output Calendar - B.C. Style year
    } // Gregorian Calculation - Ash Wednesday - Gregorian Output Calendar

    SECTION("Julian Output Calendar")
    {
      std::shared_ptr<ICalculationMethod> outputCalendar{std::make_shared<JulianOutputCalendar>(targetMethod)};

      SECTION("A.D. Style year")
      {
        Date posDate{outputCalendar->calculate(posYear)};
        REQUIRE(posDate.year == 2019);
        REQUIRE(posDate.month == 2);
        REQUIRE(posDate.day == 21);

        Date zeroDate{outputCalendar->calculate(zeroYear)};
        REQUIRE(zeroDate.year == 0);
        REQUIRE(zeroDate.month == 2);
        REQUIRE(zeroDate.day == 25);

        Date negDate{outputCalendar->calculate(negYear)};
        REQUIRE(negDate.year == -1);
        REQUIRE(negDate.month == 2);
        REQUIRE(negDate.day == 4);
      } // Gregorian Calculation - Ash Wednesday - Julian Output Calendar - A.D. Style year

      SECTION("Byzantine Style year")
      {
        std::shared_ptr<ICalculationMethod> byzantine{std::make_shared<ByzantineDate>(outputCalendar)};

        Date posDate{byzantine->calculate(posYear)};
        REQUIRE(posDate.year == 7527);
        REQUIRE(posDate.month == 2);
        REQUIRE(posDate.day == 21);

        Date zeroDate{byzantine->calculate(zeroYear)};
        REQUIRE(zeroDate.year == 5508);
        REQUIRE(zeroDate.month == 2);
        REQUIRE(zeroDate.day == 25);

        Date negDate{byzantine->calculate(negYear)};
        REQUIRE(negDate.year == 5507);
        REQUIRE(negDate.month == 2);
        REQUIRE(negDate.day == 4);
      } // Gregorian Calculation - Ash Wednesday - Julian Output Calendar - B.C. Style year
    } // Gregorian Calculation - Ash Wednesday - Julian Output Calendar

    SECTION("Revised Julian Output Calendar")
    {
      std::shared_ptr<ICalculationMethod> outputCalendar{std::make_shared<RevisedJulianOutputCalendar>(targetMethod)};

      SECTION("A.D. Style year")
      {
        Date posDate{outputCalendar->calculate(posYear)};
        REQUIRE(posDate.year == 2019);
        REQUIRE(posDate.month == 3);
        REQUIRE(posDate.day == 6);

        Date zeroDate{outputCalendar->calculate(zeroYear)};
        REQUIRE(zeroDate.year == 0);
        REQUIRE(zeroDate.month == 2);
        REQUIRE(zeroDate.day == 22);

        Date negDate{outputCalendar->calculate(negYear)};
        REQUIRE(negDate.year == -1);
        REQUIRE(negDate.month == 2);
        REQUIRE(negDate.day == 1);
      } // Gregorian Calculation - Ash Wednesday - Revised Julian Output Calendar - A.D. Style year

      SECTION("Byzantine Style year")
      {
        std::shared_ptr<ICalculationMethod> byzantine{std::make_shared<ByzantineDate>(outputCalendar)};

        Date posDate{byzantine->calculate(posYear)};
        REQUIRE(posDate.year == 7527);
        REQUIRE(posDate.month == 3);
        REQUIRE(posDate.day == 6);

        Date zeroDate{byzantine->calculate(zeroYear)};
        REQUIRE(zeroDate.year == 5508);
        REQUIRE(zeroDate.month == 2);
        REQUIRE(zeroDate.day == 22);

        Date negDate{byzantine->calculate(negYear)};
        REQUIRE(negDate.year == 5507);
        REQUIRE(negDate.month == 2);
        REQUIRE(negDate.day == 1);
      } // Gregorian Calculation - Ash Wednesday - Revised Julian Output Calendar - B.C. Style year
    } // Gregorian Calculation - Ash Wednesday - Revised Julian Output Calendar
  } // Gregorian Calculation - Ash Wednesday

  SECTION("Midfeast of Pentecost")
  {
    std::shared_ptr<ICalculationMethod> targetMethod{std::make_shared<MidfeastPentecost>(method)};

    SECTION("Gregorian Output Calendar")
    {
      SECTION("A.D. Style year")
      {
        Date posDate{targetMethod->calculate(posYear)};
        REQUIRE(posDate.year == 2019);
        REQUIRE(posDate.month == 5);
        REQUIRE(posDate.day == 15);

        Date zeroDate{targetMethod->calculate(zeroYear)};
        REQUIRE(zeroDate.year == 0);
        REQUIRE(zeroDate.month == 5);
        REQUIRE(zeroDate.day == 3);

        Date negDate{targetMethod->calculate(negYear)};
        REQUIRE(negDate.year == -1);
        REQUIRE(negDate.month == 4);
        REQUIRE(negDate.day == 13);
      } // Gregorian Calculation - Midfeast of Pentecost - Gregorian Output Calendar - A.D. Style year

      SECTION("Byzantine Style year")
      {
        std::shared_ptr<ICalculationMethod> byzantine{std::make_shared<ByzantineDate>(targetMethod)};

        Date posDate{byzantine->calculate(posYear)};
        REQUIRE(posDate.year == 7527);
        REQUIRE(posDate.month == 5);
        REQUIRE(posDate.day == 15);

        Date zeroDate{byzantine->calculate(zeroYear)};
        REQUIRE(zeroDate.year == 5508);
        REQUIRE(zeroDate.month == 5);
        REQUIRE(zeroDate.day == 3);

        Date negDate{byzantine->calculate(negYear)};
        REQUIRE(negDate.year == 5507);
        REQUIRE(negDate.month == 4);
        REQUIRE(negDate.day == 13);
      } // Gregorian Calculation - Midfeast of Pentecost - Gregorian Output Calendar - B.C. Style year
    } // Gregorian Calculation - Midfeast of Pentecost - Gregorian Output Calendar

    SECTION("Julian Output Calendar")
    {
      std::shared_ptr<ICalculationMethod> outputCalendar{std::make_shared<JulianOutputCalendar>(targetMethod)};

      SECTION("A.D. Style year")
      {
        Date posDate{outputCalendar->calculate(posYear)};
        REQUIRE(posDate.year == 2019);
        REQUIRE(posDate.month == 5);
        REQUIRE(posDate.day == 2);

        Date zeroDate{outputCalendar->calculate(zeroYear)};
        REQUIRE(zeroDate.year == 0);
        REQUIRE(zeroDate.month == 5);
        REQUIRE(zeroDate.day == 5);

        Date negDate{outputCalendar->calculate(negYear)};
        REQUIRE(negDate.year == -1);
        REQUIRE(negDate.month == 4);
        REQUIRE(negDate.day == 15);
      } // Gregorian Calculation - Midfeast of Pentecost - Julian Output Calendar - A.D. Style year

      SECTION("Byzantine Style year")
      {
        std::shared_ptr<ICalculationMethod> byzantine{std::make_shared<ByzantineDate>(outputCalendar)};

        Date posDate{byzantine->calculate(posYear)};
        REQUIRE(posDate.year == 7527);
        REQUIRE(posDate.month == 5);
        REQUIRE(posDate.day == 2);

        Date zeroDate{byzantine->calculate(zeroYear)};
        REQUIRE(zeroDate.year == 5508);
        REQUIRE(zeroDate.month == 5);
        REQUIRE(zeroDate.day == 5);

        Date negDate{byzantine->calculate(negYear)};
        REQUIRE(negDate.year == 5507);
        REQUIRE(negDate.month == 4);
        REQUIRE(negDate.day == 15);
      } // Gregorian Calculation - Midfeast of Pentecost - Julian Output Calendar - B.C. Style year
    } // Gregorian Calculation - Midfeast of Pentecost - Julian Output Calendar

    SECTION("Revised Julian Output Calendar")
    {
      std::shared_ptr<ICalculationMethod> outputCalendar{std::make_shared<RevisedJulianOutputCalendar>(targetMethod)};

      SECTION("A.D. Style year")
      {
        Date posDate{outputCalendar->calculate(posYear)};
        REQUIRE(posDate.year == 2019);
        REQUIRE(posDate.month == 5);
        REQUIRE(posDate.day == 15);

        Date zeroDate{outputCalendar->calculate(zeroYear)};
        REQUIRE(zeroDate.year == 0);
        REQUIRE(zeroDate.month == 5);
        REQUIRE(zeroDate.day == 3);

        Date negDate{outputCalendar->calculate(negYear)};
        REQUIRE(negDate.year == -1);
        REQUIRE(negDate.month == 4);
        REQUIRE(negDate.day == 12);
      } // Gregorian Calculation - Midfeast of Pentecost - Revised Julian Output Calendar - A.D. Style year

      SECTION("Byzantine Style year")
      {
        std::shared_ptr<ICalculationMethod> byzantine{std::make_shared<ByzantineDate>(outputCalendar)};

        Date posDate{byzantine->calculate(posYear)};
        REQUIRE(posDate.year == 7527);
        REQUIRE(posDate.month == 5);
        REQUIRE(posDate.day == 15);

        Date zeroDate{byzantine->calculate(zeroYear)};
        REQUIRE(zeroDate.year == 5508);
        REQUIRE(zeroDate.month == 5);
        REQUIRE(zeroDate.day == 3);

        Date negDate{byzantine->calculate(negYear)};
        REQUIRE(negDate.year == 5507);
        REQUIRE(negDate.month == 4);
        REQUIRE(negDate.day == 12);
      } // Gregorian Calculation - Midfeast of Pentecost - Revised Julian Output Calendar - B.C. Style year
    } // Gregorian Calculation - Midfeast of Pentecost - Revised Julian Output Calendar
  } // Gregorian Calculation - Midfeast of Pentecost

  SECTION("Leavetaking of Pascha")
  {
    std::shared_ptr<ICalculationMethod> targetMethod{std::make_shared<LeavetakingPascha>(method)};

    SECTION("Gregorian Output Calendar")
    {
      SECTION("A.D. Style year")
      {
        Date posDate{targetMethod->calculate(posYear)};
        REQUIRE(posDate.year == 2019);
        REQUIRE(posDate.month == 5);
        REQUIRE(posDate.day == 29);

        Date zeroDate{targetMethod->calculate(zeroYear)};
        REQUIRE(zeroDate.year == 0);
        REQUIRE(zeroDate.month == 5);
        REQUIRE(zeroDate.day == 17);

        Date negDate{targetMethod->calculate(negYear)};
        REQUIRE(negDate.year == -1);
        REQUIRE(negDate.month == 4);
        REQUIRE(negDate.day == 27);
      } // Gregorian Calculation - Leavetaking of Pascha - Gregorian Output Calendar - A.D. Style year

      SECTION("Byzantine Style year")
      {
        std::shared_ptr<ICalculationMethod> byzantine{std::make_shared<ByzantineDate>(targetMethod)};

        Date posDate{byzantine->calculate(posYear)};
        REQUIRE(posDate.year == 7527);
        REQUIRE(posDate.month == 5);
        REQUIRE(posDate.day == 29);

        Date zeroDate{byzantine->calculate(zeroYear)};
        REQUIRE(zeroDate.year == 5508);
        REQUIRE(zeroDate.month == 5);
        REQUIRE(zeroDate.day == 17);

        Date negDate{byzantine->calculate(negYear)};
        REQUIRE(negDate.year == 5507);
        REQUIRE(negDate.month == 4);
        REQUIRE(negDate.day == 27);
      } // Gregorian Calculation - Leavetaking of Pascha - Gregorian Output Calendar - B.C. Style year
    } // Gregorian Calculation - Leavetaking of Pascha - Gregorian Output Calendar

    SECTION("Julian Output Calendar")
    {
      std::shared_ptr<ICalculationMethod> outputCalendar{std::make_shared<JulianOutputCalendar>(targetMethod)};

      SECTION("A.D. Style year")
      {
        Date posDate{outputCalendar->calculate(posYear)};
        REQUIRE(posDate.year == 2019);
        REQUIRE(posDate.month == 5);
        REQUIRE(posDate.day == 16);

        Date zeroDate{outputCalendar->calculate(zeroYear)};
        REQUIRE(zeroDate.year == 0);
        REQUIRE(zeroDate.month == 5);
        REQUIRE(zeroDate.day == 19);

        Date negDate{outputCalendar->calculate(negYear)};
        REQUIRE(negDate.year == -1);
        REQUIRE(negDate.month == 4);
        REQUIRE(negDate.day == 29);
      } // Gregorian Calculation - Leavetaking of Pascha - Julian Output Calendar - A.D. Style year

      SECTION("Byzantine Style year")
      {
        std::shared_ptr<ICalculationMethod> byzantine{std::make_shared<ByzantineDate>(outputCalendar)};

        Date posDate{byzantine->calculate(posYear)};
        REQUIRE(posDate.year == 7527);
        REQUIRE(posDate.month == 5);
        REQUIRE(posDate.day == 16);

        Date zeroDate{byzantine->calculate(zeroYear)};
        REQUIRE(zeroDate.year == 5508);
        REQUIRE(zeroDate.month == 5);
        REQUIRE(zeroDate.day == 19);

        Date negDate{byzantine->calculate(negYear)};
        REQUIRE(negDate.year == 5507);
        REQUIRE(negDate.month == 4);
        REQUIRE(negDate.day == 29);
      } // Gregorian Calculation - Leavetaking of Pascha - Julian Output Calendar - B.C. Style year
    } // Gregorian Calculation - Leavetaking of Pascha - Julian Output Calendar

    SECTION("Revised Julian Output Calendar")
    {
      std::shared_ptr<ICalculationMethod> outputCalendar{std::make_shared<RevisedJulianOutputCalendar>(targetMethod)};

      SECTION("A.D. Style year")
      {
        Date posDate{outputCalendar->calculate(posYear)};
        REQUIRE(posDate.year == 2019);
        REQUIRE(posDate.month == 5);
        REQUIRE(posDate.day == 29);

        Date zeroDate{outputCalendar->calculate(zeroYear)};
        REQUIRE(zeroDate.year == 0);
        REQUIRE(zeroDate.month == 5);
        REQUIRE(zeroDate.day == 17);

        Date negDate{outputCalendar->calculate(negYear)};
        REQUIRE(negDate.year == -1);
        REQUIRE(negDate.month == 4);
        REQUIRE(negDate.day == 26);
      } // Gregorian Calculation - Leavetaking of Pascha - Revised Julian Output Calendar - A.D. Style year

      SECTION("Byzantine Style year")
      {
        std::shared_ptr<ICalculationMethod> byzantine{std::make_shared<ByzantineDate>(outputCalendar)};

        Date posDate{byzantine->calculate(posYear)};
        REQUIRE(posDate.year == 7527);
        REQUIRE(posDate.month == 5);
        REQUIRE(posDate.day == 29);

        Date zeroDate{byzantine->calculate(zeroYear)};
        REQUIRE(zeroDate.year == 5508);
        REQUIRE(zeroDate.month == 5);
        REQUIRE(zeroDate.day == 17);

        Date negDate{byzantine->calculate(negYear)};
        REQUIRE(negDate.year == 5507);
        REQUIRE(negDate.month == 4);
        REQUIRE(negDate.day == 26);
      } // Gregorian Calculation - Leavetaking of Pascha - Revised Julian Output Calendar - B.C. Style year
    } // Gregorian Calculation - Leavetaking of Pascha - Revised Julian Output Calendar
  } // Gregorian Calculation - Leavetaking of Pascha

  SECTION("Ascension")
  {
    std::shared_ptr<ICalculationMethod> targetMethod{std::make_shared<Ascension>(method)};

    SECTION("Gregorian Output Calendar")
    {
      SECTION("A.D. Style year")
      {
        Date posDate{targetMethod->calculate(posYear)};
        REQUIRE(posDate.year == 2019);
        REQUIRE(posDate.month == 5);
        REQUIRE(posDate.day == 30);

        Date zeroDate{targetMethod->calculate(zeroYear)};
        REQUIRE(zeroDate.year == 0);
        REQUIRE(zeroDate.month == 5);
        REQUIRE(zeroDate.day == 18);

        Date negDate{targetMethod->calculate(negYear)};
        REQUIRE(negDate.year == -1);
        REQUIRE(negDate.month == 4);
        REQUIRE(negDate.day == 28);
      } // Gregorian Calculation - Ascension - Gregorian Output Calendar - A.D. Style year

      SECTION("Byzantine Style year")
      {
        std::shared_ptr<ICalculationMethod> byzantine{std::make_shared<ByzantineDate>(targetMethod)};

        Date posDate{byzantine->calculate(posYear)};
        REQUIRE(posDate.year == 7527);
        REQUIRE(posDate.month == 5);
        REQUIRE(posDate.day == 30);

        Date zeroDate{byzantine->calculate(zeroYear)};
        REQUIRE(zeroDate.year == 5508);
        REQUIRE(zeroDate.month == 5);
        REQUIRE(zeroDate.day == 18);

        Date negDate{byzantine->calculate(negYear)};
        REQUIRE(negDate.year == 5507);
        REQUIRE(negDate.month == 4);
        REQUIRE(negDate.day == 28);
      } // Gregorian Calculation - Ascension - Gregorian Output Calendar - B.C. Style year
    } // Gregorian Calculation - Ascension - Gregorian Output Calendar

    SECTION("Julian Output Calendar")
    {
      std::shared_ptr<ICalculationMethod> outputCalendar{std::make_shared<JulianOutputCalendar>(targetMethod)};

      SECTION("A.D. Style year")
      {
        Date posDate{outputCalendar->calculate(posYear)};
        REQUIRE(posDate.year == 2019);
        REQUIRE(posDate.month == 5);
        REQUIRE(posDate.day == 17);

        Date zeroDate{outputCalendar->calculate(zeroYear)};
        REQUIRE(zeroDate.year == 0);
        REQUIRE(zeroDate.month == 5);
        REQUIRE(zeroDate.day == 20);

        Date negDate{outputCalendar->calculate(negYear)};
        REQUIRE(negDate.year == -1);
        REQUIRE(negDate.month == 4);
        REQUIRE(negDate.day == 30);
      } // Gregorian Calculation - Ascension - Julian Output Calendar - A.D. Style year

      SECTION("Byzantine Style year")
      {
        std::shared_ptr<ICalculationMethod> byzantine{std::make_shared<ByzantineDate>(outputCalendar)};

        Date posDate{byzantine->calculate(posYear)};
        REQUIRE(posDate.year == 7527);
        REQUIRE(posDate.month == 5);
        REQUIRE(posDate.day == 17);

        Date zeroDate{byzantine->calculate(zeroYear)};
        REQUIRE(zeroDate.year == 5508);
        REQUIRE(zeroDate.month == 5);
        REQUIRE(zeroDate.day == 20);

        Date negDate{byzantine->calculate(negYear)};
        REQUIRE(negDate.year == 5507);
        REQUIRE(negDate.month == 4);
        REQUIRE(negDate.day == 30);
      } // Gregorian Calculation - Ascension - Julian Output Calendar - B.C. Style year
    } // Gregorian Calculation - Ascension - Julian Output Calendar

    SECTION("Revised Julian Output Calendar")
    {
      std::shared_ptr<ICalculationMethod> outputCalendar{std::make_shared<RevisedJulianOutputCalendar>(targetMethod)};

      SECTION("A.D. Style year")
      {
        Date posDate{outputCalendar->calculate(posYear)};
        REQUIRE(posDate.year == 2019);
        REQUIRE(posDate.month == 5);
        REQUIRE(posDate.day == 30);

        Date zeroDate{outputCalendar->calculate(zeroYear)};
        REQUIRE(zeroDate.year == 0);
        REQUIRE(zeroDate.month == 5);
        REQUIRE(zeroDate.day == 18);

        Date negDate{outputCalendar->calculate(negYear)};
        REQUIRE(negDate.year == -1);
        REQUIRE(negDate.month == 4);
        REQUIRE(negDate.day == 27);
      } // Gregorian Calculation - Ascension - Revised Julian Output Calendar - A.D. Style year

      SECTION("Byzantine Style year")
      {
        std::shared_ptr<ICalculationMethod> byzantine{std::make_shared<ByzantineDate>(outputCalendar)};

        Date posDate{byzantine->calculate(posYear)};
        REQUIRE(posDate.year == 7527);
        REQUIRE(posDate.month == 5);
        REQUIRE(posDate.day == 30);

        Date zeroDate{byzantine->calculate(zeroYear)};
        REQUIRE(zeroDate.year == 5508);
        REQUIRE(zeroDate.month == 5);
        REQUIRE(zeroDate.day == 18);

        Date negDate{byzantine->calculate(negYear)};
        REQUIRE(negDate.year == 5507);
        REQUIRE(negDate.month == 4);
        REQUIRE(negDate.day == 27);
      } // Gregorian Calculation - Ascension - Revised Julian Output Calendar - B.C. Style year
    } // Gregorian Calculation - Ascension - Revised Julian Output Calendar
  } // Gregorian Calculation - Ascension

  SECTION("Pentecost")
  {
    std::shared_ptr<ICalculationMethod> targetMethod{std::make_shared<Pentecost>(method)};

    SECTION("Gregorian Output Calendar")
    {
      SECTION("A.D. Style year")
      {
        Date posDate{targetMethod->calculate(posYear)};
        REQUIRE(posDate.year == 2019);
        REQUIRE(posDate.month == 6);
        REQUIRE(posDate.day == 9);

        Date zeroDate{targetMethod->calculate(zeroYear)};
        REQUIRE(zeroDate.year == 0);
        REQUIRE(zeroDate.month == 5);
        REQUIRE(zeroDate.day == 28);

        Date negDate{targetMethod->calculate(negYear)};
        REQUIRE(negDate.year == -1);
        REQUIRE(negDate.month == 5);
        REQUIRE(negDate.day == 8);
      } // Gregorian Calculation - Pentecost - Gregorian Output Calendar - A.D. Style year

      SECTION("Byzantine Style year")
      {
        std::shared_ptr<ICalculationMethod> byzantine{std::make_shared<ByzantineDate>(targetMethod)};

        Date posDate{byzantine->calculate(posYear)};
        REQUIRE(posDate.year == 7527);
        REQUIRE(posDate.month == 6);
        REQUIRE(posDate.day == 9);

        Date zeroDate{byzantine->calculate(zeroYear)};
        REQUIRE(zeroDate.year == 5508);
        REQUIRE(zeroDate.month == 5);
        REQUIRE(zeroDate.day == 28);

        Date negDate{byzantine->calculate(negYear)};
        REQUIRE(negDate.year == 5507);
        REQUIRE(negDate.month == 5);
        REQUIRE(negDate.day == 8);
      } // Gregorian Calculation - Pentecost - Gregorian Output Calendar - B.C. Style year
    } // Gregorian Calculation - Pentecost - Gregorian Output Calendar

    SECTION("Julian Output Calendar")
    {
      std::shared_ptr<ICalculationMethod> outputCalendar{std::make_shared<JulianOutputCalendar>(targetMethod)};

      SECTION("A.D. Style year")
      {
        Date posDate{outputCalendar->calculate(posYear)};
        REQUIRE(posDate.year == 2019);
        REQUIRE(posDate.month == 5);
        REQUIRE(posDate.day == 27);

        Date zeroDate{outputCalendar->calculate(zeroYear)};
        REQUIRE(zeroDate.year == 0);
        REQUIRE(zeroDate.month == 5);
        REQUIRE(zeroDate.day == 30);

        Date negDate{outputCalendar->calculate(negYear)};
        REQUIRE(negDate.year == -1);
        REQUIRE(negDate.month == 5);
        REQUIRE(negDate.day == 10);
      } // Gregorian Calculation - Pentecost - Julian Output Calendar - A.D. Style year

      SECTION("Byzantine Style year")
      {
        std::shared_ptr<ICalculationMethod> byzantine{std::make_shared<ByzantineDate>(outputCalendar)};

        Date posDate{byzantine->calculate(posYear)};
        REQUIRE(posDate.year == 7527);
        REQUIRE(posDate.month == 5);
        REQUIRE(posDate.day == 27);

        Date zeroDate{byzantine->calculate(zeroYear)};
        REQUIRE(zeroDate.year == 5508);
        REQUIRE(zeroDate.month == 5);
        REQUIRE(zeroDate.day == 30);

        Date negDate{byzantine->calculate(negYear)};
        REQUIRE(negDate.year == 5507);
        REQUIRE(negDate.month == 5);
        REQUIRE(negDate.day == 10);
      } // Gregorian Calculation - Pentecost - Julian Output Calendar - B.C. Style year
    } // Gregorian Calculation - Pentecost - Julian Output Calendar

    SECTION("Revised Julian Output Calendar")
    {
      std::shared_ptr<ICalculationMethod> outputCalendar{std::make_shared<RevisedJulianOutputCalendar>(targetMethod)};

      SECTION("A.D. Style year")
      {
        Date posDate{outputCalendar->calculate(posYear)};
        REQUIRE(posDate.year == 2019);
        REQUIRE(posDate.month == 6);
        REQUIRE(posDate.day == 9);

        Date zeroDate{outputCalendar->calculate(zeroYear)};
        REQUIRE(zeroDate.year == 0);
        REQUIRE(zeroDate.month == 5);
        REQUIRE(zeroDate.day == 28);

        Date negDate{outputCalendar->calculate(negYear)};
        REQUIRE(negDate.year == -1);
        REQUIRE(negDate.month == 5);
        REQUIRE(negDate.day == 7);
      } // Gregorian Calculation - Pentecost - Revised Julian Output Calendar - A.D. Style year

      SECTION("Byzantine Style year")
      {
        std::shared_ptr<ICalculationMethod> byzantine{std::make_shared<ByzantineDate>(outputCalendar)};

        Date posDate{byzantine->calculate(posYear)};
        REQUIRE(posDate.year == 7527);
        REQUIRE(posDate.month == 6);
        REQUIRE(posDate.day == 9);

        Date zeroDate{byzantine->calculate(zeroYear)};
        REQUIRE(zeroDate.year == 5508);
        REQUIRE(zeroDate.month == 5);
        REQUIRE(zeroDate.day == 28);

        Date negDate{byzantine->calculate(negYear)};
        REQUIRE(negDate.year == 5507);
        REQUIRE(negDate.month == 5);
        REQUIRE(negDate.day == 7);
      } // Gregorian Calculation - Pentecost - Revised Julian Output Calendar - B.C. Style year
    } // Gregorian Calculation - Pentecost - Revised Julian Output Calendar
  } // Gregorian Calculation - Pentecost
} // Gregorian Calculation
