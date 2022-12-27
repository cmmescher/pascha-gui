#include "app.h"

#include "config_io.h"
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
  m_view = makeView();
  m_view->createView();

  return true;
} // App::OnInit()

wxGuiView* App::makeView()
{
  Configuration config = readConfigFile();

  std::string pascha_name = "Pascha";
  if (!config.pascha_name.empty()) {
    pascha_name = (config.pascha_name == "Easter") ? "Easter" : "Pascha";
  }

  DateFormat date_format = DateFormat::YMD;
  if (config.date_format == "MDY") {
    date_format = DateFormat::MDY;
  } else if (config.date_format == "DMY") {
    date_format = DateFormat::DMY;
  }

  std::string date_separator = "/";
  if (!config.date_separator.empty()) { date_separator = config.date_separator; }

  return new wxGuiView{*m_controller, *m_model, pascha_name, date_format,
                       date_separator};
} // App::makeView()

} // namespace pascha
