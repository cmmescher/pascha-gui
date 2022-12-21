#ifndef PASCHA_PASCHA_CALCULATOR_MODEL_H
#define PASCHA_PASCHA_CALCULATOR_MODEL_H

#include "i_calculator_model.h"
#include <vector>
namespace pascha
{

class PaschaCalculatorModel : public ICalculatorModel
{
 public:
  PaschaCalculatorModel() = default;
  PaschaCalculatorModel(const PaschaCalculatorModel&) = delete;
  PaschaCalculatorModel(PaschaCalculatorModel&&) = delete;
  PaschaCalculatorModel& operator=(const PaschaCalculatorModel&) = delete;
  PaschaCalculatorModel& operator=(PaschaCalculatorModel&&) = delete;
  virtual ~PaschaCalculatorModel() = default;

  virtual void
      setCalculationMethod(std::unique_ptr<ICalculationMethod>) override;
  virtual void calculate(Year) const override;
  virtual void daysUntil(Year) const override;
  virtual void weeksBetween(Year, std::unique_ptr<ICalculationMethod>,
                            std::unique_ptr<ICalculationMethod>) const override;
  virtual void addObserver(IObserver&) override;
  virtual void removeObserver(IObserver&) override;
  virtual void notify(const OutputDate&) const override;
  virtual void notify(Weeks) const override;
  virtual void notify(Days) const override;
  virtual void notify(std::string_view) const override;

 private:
  std::unique_ptr<ICalculationMethod> m_calculation_method{nullptr};
  std::vector<IObserver*> m_observers{};
}; // class PaschaCalculatorModel

} // namespace pascha
#endif // !PASCHA_PASCHA_CALCULATOR_MODEL_H
