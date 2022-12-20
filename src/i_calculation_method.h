#ifndef PASCHA_I_CALCULATION_METHOD_H
#define PASCHA_I_CALCULATION_METHOD_H

#include "date.h"
#include "typedefs.h"

namespace pascha
{

class ICalculationMethod
{
 public:
  virtual ~ICalculationMethod() = default;
  virtual Date calculate(Year) const = 0;
}; // class ICalculationMethod

} // namespace pascha

#endif // !PASCHA_I_CALCULATION_METHOD_H
