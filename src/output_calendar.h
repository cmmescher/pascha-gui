#ifndef PASCHA_OUTPUT_CALENDAR_H
#define PASCHA_OUTPUT_CALENDAR_H

#include "calculation_method_decorator.h"
#include "i_calculation_method.h"

#include <memory>

namespace pascha
{

class OutputCalendar : public CalculationMethodDecorator
{
 public:
  OutputCalendar(std::unique_ptr<ICalculationMethod> calculation_method)
    : CalculationMethodDecorator(std::move(calculation_method)) {}
  virtual ~OutputCalendar() = default;
}; // class OutputCalendar

} // namespace pascha

#endif // !PASCHA_OUTPUT_CALENDAR_H
