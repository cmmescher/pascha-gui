// Copyright (C) 2022, 2024 Christopher Michael Mescher
//
// pascha-gui: A GUI Pascha (Easter) date calculator.
//
// Version: 1.0 (2024-01-07)
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

#ifndef PASCHA_APP_H
#define PASCHA_APP_H

#include "wxGuiView.h"

#include "wx/wx.h"

#include <memory>
#include <string>

namespace pascha
{

class App : public wxApp
{
 public:
  virtual bool OnInit();

 private:
  wxGuiView* m_view{};
  std::unique_ptr<ICalculatorModel> m_model{};
  std::unique_ptr<IController> m_controller{};

  wxGuiView* makeView();
}; // class App

} // namespace pascha
#endif // !PASCHA_APP_H
