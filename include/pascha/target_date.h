#ifndef PASCHA_TARGET_DATE_H
#define PASCHA_TARGET_DATE_H

#include "calculation_method_decorator.h"
#include "date.h"
#include "i_calculation_method.h"

#include <memory>

namespace pascha
{

class TargetDate : public CalculationMethodDecorator
{
 public:
  TargetDate(std::shared_ptr<ICalculationMethod> calculation_method, int shift_amount)
    : CalculationMethodDecorator{calculation_method}, m_shift_amount{shift_amount} {}
  virtual ~TargetDate() = default;
  Date calculate(Year) const override;

 private:
  int m_shift_amount{};
  void shift(int, Date&) const;
}; // class TargetDate

} // namespace pascha

#endif // !PASCHA_TARGET_DATE_H
