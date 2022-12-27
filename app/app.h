#ifndef PASCHA_APP_H
#define PASCHA_APP_H

#include "wxGuiView.h"

#include "wx/wx.h"

#include <memory>

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
}; // class App

} // namespace pascha
#endif // !PASCHA_APP_H
