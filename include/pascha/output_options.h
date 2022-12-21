#ifndef PASCHA_OUTPUT_OPTIONS_H
#define PASCHA_OUTPUT_OPTIONS_H

#include "output_option.h"

namespace pascha
{

class ByzantineDate : public OutputOption
{
 public:
  ByzantineDate(std::unique_ptr<ICalculationMethod> calculation_method)
    : OutputOption(std::move(calculation_method)) {}
  Date calculate(Year) const override;
}; // class ByzantineDate

} // namespace pascha
#endif // !PASCHA_OUTPUT_OPTIONS_H
