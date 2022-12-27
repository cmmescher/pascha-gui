#include "app.h"

#include "wxGuiView.h"

#include "pascha/gui_controller.h"
#include "pascha/pascha_calculator_model.h"

wxIMPLEMENT_APP(pascha::App);

namespace pascha
{

bool App::OnInit()
{
  m_model = std::make_unique<PaschaCalculatorModel>();
  m_controller = std::make_unique<GuiController>(*m_model);
  m_view = new wxGuiView{*m_controller, *m_model};
  m_view->createView();

  return true;
} // App::OnInit()

} // namespace pascha
