#ifndef PASCHA_OUTPUT_OPTIONS_H
#define PASCHA_OUTPUT_OPTIONS_H

#include "output_option.h"

namespace pascha
{

class ByzantineDate : public OutputOption
{
 public:
  ByzantineDate(std::shared_ptr<ICalculationMethod> calculation_method)
    : OutputOption{calculation_method} {}
  ~ByzantineDate() = default;
  Date calculate(Year) const override;
}; // class ByzantineDate

} // namespace pascha
#endif // !PASCHA_OUTPUT_OPTIONS_H
