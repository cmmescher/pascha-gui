// Copyright (C) 2022, 2024 Christopher Michael Mescher
//
// pascha-gui: A GUI Pascha (Easter) date calculator.
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>.
//
// Contact !(echo \<pascha-mescher+faith\>|sed s/\+/./g\;s/\-/@/) for bug
// reporting.

#ifndef PASCHA_GUI_CONTROLLER_H
#define PASCHA_GUI_CONTROLLER_H

#include "pascha/i_controller.h"
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
