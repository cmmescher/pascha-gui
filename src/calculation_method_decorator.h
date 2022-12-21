#ifndef PACHA_CALCULATION_METHOD_DECORATOR_H
#define PACHA_CALCULATION_METHOD_DECORATOR_H

#include "i_calculation_method.h"

#include <memory>

namespace pascha
{

class CalculationMethodDecorator : public ICalculationMethod
{
 public:
  CalculationMethodDecorator(std::shared_ptr<ICalculationMethod>);
  virtual ~CalculationMethodDecorator() = default;
  virtual Date calculate(Year) const override;

 protected:
  const ICalculationMethod& calculation_method() const
    { return *m_calculation_method; }
 private:
  std::shared_ptr<ICalculationMethod> m_calculation_method{};
}; // class CalculationMethodDecorator

} // namespace pascha

#endif // !PACHA_CALCULATION_METHOD_DECORATOR_H
