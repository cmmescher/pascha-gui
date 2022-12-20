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
  TargetDate(std::unique_ptr<ICalculationMethod> calculation_method, std::int64_t shift_amount)
    : CalculationMethodDecorator(std::move(calculation_method)) {}
  virtual ~TargetDate() = default;
  Date calculate(Year) const override;

 private:
  std::int64_t m_shift_amount;
  void shift(std::int64_t, Date&) const;
}; // class TargetDate

} // namespace pascha

#endif // !PASCHA_TARGET_DATE_H
