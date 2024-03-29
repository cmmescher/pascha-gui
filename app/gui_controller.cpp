// Copyright (C) 2022, 2024 Christopher Michael Mescher
//
// pascha-gui: A GUI Pascha (Easter) date calculator.
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

#include "gui_controller.h"

#include "pascha/calculation_methods.h"
#include "pascha/output_calendars.h"
#include "pascha/output_options.h"
#include "pascha/target_dates.h"

namespace pascha
{

GuiController::GuiController(ICalculatorModel& model)
    : m_model{&model} {} // GuiController::GuiController

void GuiController::calculate(const CalculationOptions& options) const
{
  using namespace std::literals; // for sv

  // Ensure the year is valid before continuing.
  if (!validateYear(options.year)) {
    m_model->notify("Invalid year"sv);
    return;
  }

  // Check if we are calculating weeks between two methods, before creating the
  // method object.
  // If so, perform the calculation and return.
  if (options.target_outputs.front() == e_target_output::weeksBetween) {
    std::unique_ptr<ICalculationMethod> julian_method{
        new JulianCalculationMethod{}};
    std::unique_ptr<ICalculationMethod> gregorian_method{
        new GregorianCalculationMethod{}};
    m_model->weeksBetween(options.year, std::move(julian_method),
                          std::move(gregorian_method));
    return;
  }

  std::unique_ptr<ICalculationMethod> method{nullptr};

  // 1. get the calculation method from the options.
  // Default to Julian.
  switch (options.calculation_method) {
    case e_calculation_method::gregorian: {
      method =
          std::unique_ptr<ICalculationMethod>{new GregorianCalculationMethod{}};
      break;
    }
    default: {
      method =
          std::unique_ptr<ICalculationMethod>{new JulianCalculationMethod{}};
      break;
    }
  }

  // 2. Get the target date from the options.
  // Default to Pascha.
  switch (options.target_outputs.front()) {
    case e_target_output::daysUntil: {
      m_model->setCalculationMethod(std::move(method));
      m_model->daysUntil(options.year);
      return;
    }
    case e_target_output::meatfare: {
      method =
          std::unique_ptr<ICalculationMethod>{new Meatfare{std::move(method)}};
      break;
    }
    case e_target_output::cheesefare: {
      method = std::unique_ptr<ICalculationMethod>{
          new Cheesefare{std::move(method)}};
      break;
    }
    case e_target_output::ashWednesday: {
      method = std::unique_ptr<ICalculationMethod>{
          new AshWednesday{std::move(method)}};
      break;
    }
    case e_target_output::midfeastPentecost: {
      method = std::unique_ptr<ICalculationMethod>{
          new MidfeastPentecost{std::move(method)}};
      break;
    }
    case e_target_output::leavetakingPascha: {
      method = std::unique_ptr<ICalculationMethod>{
          new LeavetakingPascha{std::move(method)}};
      break;
    }
    case e_target_output::ascension: {
      method =
          std::unique_ptr<ICalculationMethod>{new Ascension{std::move(method)}};
      break;
    }
    case e_target_output::pentecost: {
      method =
          std::unique_ptr<ICalculationMethod>{new Pentecost{std::move(method)}};
      break;
    }
    default: {
      // Pascha is calculated by default already.
      break;
    }
  }

  // 3. Set the output calendar.
  // Default to Julian.
  switch (options.output_calendar) {
    case e_output_calendar::gregorian: {
      // Gregorian is used by default for calculations.
      break;
    }
    case e_output_calendar::rev_julian: {
      method = std::unique_ptr<ICalculationMethod>{
          new RevisedJulianOutputCalendar{std::move(method)}};
      break;
    }
    default: { // Julian
      method = std::unique_ptr<ICalculationMethod>{
          new JulianOutputCalendar{std::move(method)}};
      break;
    }
  }

  // 4. Apply the options.
  for (auto option : options.options) {
    switch (option) {
      case (e_output_option::byzantine): {
        method = std::unique_ptr<ICalculationMethod>{
            new ByzantineDate{std::move(method)}};
        break;
      }
    }
  }

  // 5. Set the calculation method and calculate.
  m_model->setCalculationMethod(std::move(method));
  m_model->calculate(options.year);
} // GuiController::calculate

void GuiController::addView(IView& view)
{
  m_views.push_back(&view);
} // GuiController::addView

void GuiController::removeView(IView& view)
{
  std::erase(m_views, &view);
} // GuiController::removeView

void GuiController::start()
{
  for (auto* view : m_views) { view->createView(); }
} // GuiController::start

bool GuiController::validateYear(const Year& year) const
{
  // TODO: add year validation
  return true;
} // GuiController::validateYear

} // namespace pascha
