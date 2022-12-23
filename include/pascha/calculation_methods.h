#ifndef PASCHA_CALCULATION_METHODS_H
#define PASCHA_CALCULATION_METHODS_H

#include "i_calculation_method.h"

namespace pascha
{

class JulianCalculationMethod : public ICalculationMethod
{
 public:
  ~JulianCalculationMethod() = default;
  Date calculate(Year year) const override;
}; // class JulianCalculationMethod

class GregorianCalculationMethod : public ICalculationMethod
{
 public:
  ~GregorianCalculationMethod() = default;
  Date calculate(Year year) const override;
}; // class GregorianCalculationMethod

} // namespace pascha

#endif // !PASCHA_CALCULATION_METHODS_H
