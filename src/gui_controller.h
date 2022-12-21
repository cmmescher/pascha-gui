#ifndef PASCHA_GUI_CONTROLLER_H
#define PASCHA_GUI_CONTROLLER_H

#include "i_controller.h"
namespace pascha
{

class GuiController : public IController
{
 public:
  GuiController(ICalculatorModel& model);
  GuiController(const GuiController&) = delete;
  GuiController(GuiController&&) = delete;
  GuiController& operator=(const GuiController&) = delete;
  GuiController& operator=(GuiController&&) = delete;
  virtual ~GuiController() = default;
  virtual void calculate(const CalculationOptions& options) const override;
  virtual void addView(IView&) override;
  virtual void removeView(IView&) override;
  virtual void start() override;

 private:
  ICalculatorModel* m_model{};
  std::vector<IView*> m_views{};
  bool validateYear(const Year& year) const;
}; // class GuiController

} // namespace pascha
#endif // !PASCHA_GUI_CONTROLLER_H
