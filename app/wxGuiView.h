#ifndef PASCHA_WXGUIVIEW_H
#define PASCHA_WXGUIVIEW_H

#include "date_format.h"

#include "pascha/i_calculator_model.h"
#include "pascha/i_controller.h"
#include "pascha/i_view.h"

#include <wx/wx.h>

#include <string>

namespace pascha
{

class wxGuiView : public IView, public wxFrame
{
 public:
  wxGuiView(IController& controller, ICalculatorModel& model);
  ~wxGuiView();

  // IView interface
  void createView() override;

  // IObserver interface (from IView)
  void update(const Date& date) override;
  void update(Weeks weeks) override;
  void update(Days days) override;
  void update(std::string_view message) override;

  // GUI Components
  wxBoxSizer* mainSizer{};
  wxStaticText* m_header{};
  wxStaticText* m_calculation_method_label{};
  wxRadioButton* m_julian_calculation_button{};
  wxRadioButton* m_gregorian_calculation_button{};
  wxStaticText* m_target_date_label{};
  wxComboBox* m_target_output_combobox{};
  wxStaticText* m_output_calendar_label{};
  wxRadioButton* m_julian_calendar_button{};
  wxRadioButton* m_gregorian_calendar_button{};
  wxRadioButton* m_revised_julian_calendar_button{};
  wxStaticText* m_options_label{};
  wxCheckBox* m_byzantine_year_checkbox{};
  wxStaticText* m_input_year_label{};
  wxTextCtrl* m_input_year_text{};
  wxButton* m_calculate_button{};
  wxStaticText* m_output_label{};
  wxStaticText* m_output_text{};

  // GUI callbacks
  void onCalculate(wxCommandEvent& evt);

  wxDECLARE_EVENT_TABLE();

  enum
  {
    id_calculate_button = wxID_HIGHEST + 1,
  };

 private:
  IController* m_controller{};
  ICalculatorModel* m_model{};
  std::string m_pascha_name{};
  DateFormat m_date_format{};
  std::string m_date_separator{};

  std::string formatDate(const Date& date) const;
}; // class wxGuiView

} // namespace pascha
#endif // !PASCHA_WXGUIVIEW_H
