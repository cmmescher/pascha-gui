#ifndef PASCHA_I_CALCULATOR_MODEL_H
#define PASCHA_I_CALCULATOR_MODEL_H

#include "i_calculation_method.h"
#include "i_observable.h"
#include "typedefs.h"

#include <iostream>
#include <memory>

namespace pascha
{

class ICalculatorModel : public IObservable
{
 public:
  virtual ~ICalculatorModel() = default;
  virtual void setCalculationMethod(std::unique_ptr<ICalculationMethod>) = 0;
  virtual void calculate(Year) const = 0;
  // Calculate the number of days until Pascha in the given year.
  virtual void daysUntil(Year) const = 0;
  // Calculate the number of days between the dates calculated by the two
  // methods, for the given year. Typically this will be between the Julian and
  // Gregorian methods for calculating Pascha.
  virtual void weeksBetween(Year, std::unique_ptr<ICalculationMethod>,
                            std::unique_ptr<ICalculationMethod>) const = 0;
}; // class ICalculatorModel

} // namespace pascha

#endif // !PASCHA_I_CALCULATOR_MODEL_H
