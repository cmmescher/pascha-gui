#ifndef PASCHA_OUTPUT_OPTION_H
#define PASCHA_OUTPUT_OPTION_H

#include "calculation_method_decorator.h"
#include "i_calculation_method.h"

#include <memory>

namespace pascha
{

class OutputOption : public CalculationMethodDecorator
{
 public:
  OutputOption(std::unique_ptr<ICalculationMethod> calculation_method)
    : CalculationMethodDecorator(std::move(calculation_method)) {}
  virtual ~OutputOption() = default;
}; // class OutputOption

class ByzantineDate : public OutputOption
{
 public:
  ByzantineDate(std::unique_ptr<ICalculationMethod> calculation_method)
    : OutputOption(std::move(calculation_method)) {}
  Date calculate(Year) const override;
}; // class ByzantineDate

} // namespace pascha

#endif // !PASCHA_OUTPUT_OPTION_H
