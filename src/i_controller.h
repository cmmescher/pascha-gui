#ifndef PASCHA_I_CONTROLLER_H
#define PASCHA_I_CONTROLLER_H

#include "calculation_options.h"
#include "i_calculator_model.h"
#include "i_view.h"

namespace pascha
{

class IController
{
 public:
  IController(ICalculatorModel& model);
  virtual ~IController();
  // Calculate the output using the model with the given options.
  virtual void calculate(const CalculationOptions& options) const = 0;
  // Start the view.
  virtual void start() = 0;
}; // class IController

} // namespace pascha

#endif // !PASCHA_I_CONTROLLER_H
