#include "pascha/pascha_calculator_model.h"

#include "pascha/calendar_conversion.h"

#include <ctime>
#include <limits>

namespace pascha
{

void PaschaCalculatorModel::setCalculationMethod(
    std::unique_ptr<ICalculationMethod> calculation_method)
{
  m_calculation_method = std::move(calculation_method);
}

void PaschaCalculatorModel::calculate(Year year) const
{
  using namespace std::literals; // for sv

  if (!m_calculation_method)
  {
    notify("No calculation method set!"sv);
    return;
  }

  try {
    Date date = m_calculation_method->calculate(year);
  } catch (const std::overflow_error& e) {
    notify(e.what());
  }
} // PaschaCalculatorModel::calculate

void PaschaCalculatorModel::daysUntil(Year year) const
{
  using namespace std::literals; // for sv

  if (!m_calculation_method)
  {
    notify("No calculation method set!"sv);
    return;
  }

  try {
    CalcInt dateJdn{gregorianToJdn(m_calculation_method->calculate(year))};

    std::time_t t = std::time(0); // get time now
    std::tm* now = std::localtime(&t);
    Date nowDate{};
    nowDate.year = now->tm_year + 1900;
    nowDate.month = now->tm_mon + 1;
    nowDate.day = now->tm_mday;
    CalcInt nowJdn{gregorianToJdn(nowDate)};

    notify(Days{dateJdn - nowJdn});
  } catch (const std::overflow_error& e) {
    notify(e.what());
  }
} // PaschaCalculatorModel::daysUntil

void PaschaCalculatorModel::weeksBetween(
    Year year, std::unique_ptr<ICalculationMethod> method1,
    std::unique_ptr<ICalculationMethod> method2) const
{
  using namespace std::literals; // for sv

  if (!method1 || !method2)
  {
    notify("No calculation method set!"sv);
    return;
  }

  try {
    CalcInt date1Jdn{gregorianToJdn(method1->calculate(year))};
    CalcInt date2Jdn{gregorianToJdn(method2->calculate(year))};

    notify(Weeks{(date1Jdn - date2Jdn) / 7});
  } catch (const std::overflow_error& e) {
    notify(e.what());
  }
} // PaschaCalculatorModel::weeksBetween

void PaschaCalculatorModel::addObserver(IObserver& observer)
{
  m_observers.push_back(&observer);
} // PaschaCalculatorModel::addObserver

void PaschaCalculatorModel::removeObserver(IObserver& observer)
{
  std::erase(m_observers, &observer);
} // PaschaCalculatorModel::removeObserver

void PaschaCalculatorModel::notify(const Date& date) const
{
  for (IObserver* observer : m_observers) {
    observer->update(date);
  }
} // PaschaCalculatorModel::notify

void PaschaCalculatorModel::notify(Weeks weeks) const
{
  for (IObserver* observer : m_observers) {
    observer->update(weeks);
  }
} // PaschaCalculatorModel::notify

void PaschaCalculatorModel::notify(Days days) const
{
  for (IObserver* observer : m_observers) {
    observer->update(days);
  }
} // PaschaCalculatorModel::notify

void PaschaCalculatorModel::notify(std::string_view message) const
{
  for (IObserver* observer : m_observers) {
    observer->update(message);
  }
} // PaschaCalculatorModel::notify

} // namespace pascha
