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
  OutputOption(std::shared_ptr<ICalculationMethod> calculation_method)
    : CalculationMethodDecorator{calculation_method} {}
  virtual ~OutputOption() = default;
}; // class OutputOption

} // namespace pascha

#endif // !PASCHA_OUTPUT_OPTION_H
