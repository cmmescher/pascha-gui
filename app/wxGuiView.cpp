#include "wxGuiView.h"

#include "pascha/calculation_options.h"

#include <fmt/core.h>
#include <wx/wrapsizer.h>

#include <chrono>
#include <ctime>
#include <string>

wxBEGIN_EVENT_TABLE(pascha::wxGuiView, wxFrame)
    EVT_BUTTON(id_calculate_button, pascha::wxGuiView::onCalculate)
        wxEND_EVENT_TABLE()

            namespace pascha
{
  wxGuiView::wxGuiView(IController & controller, ICalculatorModel & model)
      : wxFrame{nullptr, wxID_ANY, "Pascha Calculator", wxDefaultPosition,
                wxSize(600, 600)},
        m_controller{&controller},
        m_model{&model},
        m_pascha_name{"Pascha"},
        m_date_format{DateFormat::YMD},
        m_date_separator{"/"}
  {
    m_model->addObserver(*this);
    m_controller->addView(*this);

    mainSizer = new wxBoxSizer(wxVERTICAL);

    wxScrolledWindow* sw = new wxScrolledWindow(
        this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxVSCROLL);
    mainSizer->Add(sw, 1, wxEXPAND | wxALL, 5);

    wxBoxSizer* swSizer = new wxBoxSizer(wxVERTICAL);

    m_header =
        new wxStaticText(sw, wxID_ANY, "Pascha Calculator", wxDefaultPosition,
                         wxDefaultSize, wxALIGN_CENTRE);
    m_header->SetFont(wxFont(18, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL,
                             wxFONTWEIGHT_BOLD, false));
    swSizer->Add(m_header, 0, wxALL | wxEXPAND, 5);

    wxWrapSizer* calculationMethodSizer = new wxWrapSizer(wxHORIZONTAL);
    m_calculation_method_label =
        new wxStaticText(sw, wxID_ANY, "Calculation Method:");
    calculationMethodSizer->Add(m_calculation_method_label, 0, wxALL, 5);
    m_julian_calculation_button = new wxRadioButton(
        sw, wxID_ANY, "Julian", wxDefaultPosition, wxDefaultSize, wxRB_GROUP);
    calculationMethodSizer->Add(m_julian_calculation_button, 0, wxALL, 5);
    m_gregorian_calculation_button =
        new wxRadioButton(sw, wxID_ANY, "Gregorian");
    calculationMethodSizer->Add(m_gregorian_calculation_button, 0, wxALL, 5);
    m_julian_calculation_button->SetValue(true);
    swSizer->Add(calculationMethodSizer, 0, wxALL | wxEXPAND, 5);

    wxWrapSizer* targetDateSizer = new wxWrapSizer(wxHORIZONTAL);
    m_target_date_label = new wxStaticText(sw, wxID_ANY, "Target Calculation:");
    targetDateSizer->Add(m_target_date_label, 0, wxALL, 5);
    m_target_output_combobox =
        new wxComboBox(sw, wxID_ANY, "Pascha", wxDefaultPosition, wxDefaultSize,
                       0, nullptr, wxCB_READONLY);
    m_target_output_combobox->Append(m_pascha_name);
    m_target_output_combobox->Append(
        "Weeks between Julian and Gregorian Pascha");
    m_target_output_combobox->Append("Days until " + m_pascha_name);
    m_target_output_combobox->Append("Meatfare");
    m_target_output_combobox->Append("Cheesefare");
    m_target_output_combobox->Append("Ash Wednesday");
    m_target_output_combobox->Append("Midfeast of Pentecost");
    m_target_output_combobox->Append("Leavetaking of Pascha");
    m_target_output_combobox->Append("Ascension");
    m_target_output_combobox->Append("Pentecost");
    m_target_output_combobox->SetSelection(0);
    targetDateSizer->Add(m_target_output_combobox, 0, wxALL, 5);
    swSizer->Add(targetDateSizer, 0, wxALL | wxEXPAND, 5);

    wxWrapSizer* calendarSizer = new wxWrapSizer(wxHORIZONTAL);
    m_output_calendar_label =
        new wxStaticText(sw, wxID_ANY, "Output Calendar:");
    calendarSizer->Add(m_output_calendar_label, 0, wxALL, 5);
    m_julian_calendar_button = new wxRadioButton(
        sw, wxID_ANY, "Julian", wxDefaultPosition, wxDefaultSize, wxRB_GROUP);
    calendarSizer->Add(m_julian_calendar_button, 0, wxALL, 5);
    m_gregorian_calendar_button = new wxRadioButton(sw, wxID_ANY, "Gregorian");
    calendarSizer->Add(m_gregorian_calendar_button, 0, wxALL, 5);
    m_revised_julian_calendar_button =
        new wxRadioButton(sw, wxID_ANY, "Revised Julian");
    calendarSizer->Add(m_revised_julian_calendar_button, 0, wxALL, 5);
    m_julian_calendar_button->SetValue(true);
    swSizer->Add(calendarSizer, 0, wxALL | wxEXPAND, 5);

    wxWrapSizer* optionsSizer = new wxWrapSizer(wxHORIZONTAL);
    m_options_label = new wxStaticText(sw, wxID_ANY, "Options:");
    optionsSizer->Add(m_options_label, 0, wxALL, 5);
    m_byzantine_year_checkbox = new wxCheckBox(sw, wxID_ANY, "Byzantine Year");
    optionsSizer->Add(m_byzantine_year_checkbox, 0, wxALL, 5);
    swSizer->Add(optionsSizer, 0, wxALL | wxEXPAND, 5);

    wxWrapSizer* inputYearSizer = new wxWrapSizer(wxHORIZONTAL);
    m_input_year_label = new wxStaticText(sw, wxID_ANY, "Input Year:");
    inputYearSizer->Add(m_input_year_label, 0, wxALL, 5);
    auto now{std::chrono::system_clock::now()};
    auto nowTime{std::chrono::system_clock::to_time_t(now)};
    auto currYear{std::localtime(&nowTime)->tm_year + 1900};
    wxString currYearStr{std::to_string(currYear)};
    m_input_year_text = new wxTextCtrl(sw, wxID_ANY, currYearStr);
    inputYearSizer->Add(m_input_year_text, 0, wxALL, 5);
    swSizer->Add(inputYearSizer, 0, wxALL | wxEXPAND, 5);

    m_calculate_button = new wxButton(sw, id_calculate_button, "Calculate");
    swSizer->Add(m_calculate_button, 0, wxALL | wxCENTER, 5);

    wxWrapSizer* outputSizer = new wxWrapSizer(wxHORIZONTAL);
    m_output_label = new wxStaticText(sw, wxID_ANY, "");
    outputSizer->Add(m_output_label, 0, wxALL, 5);
    m_output_text = new wxStaticText(sw, wxID_ANY, "");
    outputSizer->Add(m_output_text, 0, wxALL, 5);
    swSizer->Add(outputSizer, 0, wxALL | wxEXPAND, 5);

    sw->SetSizer(swSizer);
    sw->SetScrollRate(5, 5);
    swSizer->Layout();
    this->SetSizer(mainSizer);
    mainSizer->Layout();
  } // wxGuiView::wxGuiView()

wxGuiView::~wxGuiView()
{
  m_model->removeObserver(*this);
  m_controller->removeView(*this);
}

  void wxGuiView::createView() { this->Show(); } // wxGuiView::createView()

  void wxGuiView::update(const Date& date)
  {
    m_output_label->SetLabel(
        fmt::format(fmt::runtime("{} {}:"),
                    std::string(m_target_output_combobox->GetStringSelection()),
                    std::string(m_input_year_text->GetValue())));
    m_output_text->SetLabel(formatDate(date));
  } // wxGuiView::update(const Date&)

  void wxGuiView::update(Weeks weeks)
  {
    m_output_label->SetLabel(fmt::format(
        fmt::runtime("Weeks between Julian and Gregorian Pascha {}:"),
        std::string(m_input_year_text->GetValue())));
    m_output_text->SetLabel(std::to_string(weeks.value));
  } // wxGuiView::update(Weeks)

  void wxGuiView::update(Days days)
  {
    m_output_label->SetLabel(
        fmt::format(fmt::runtime("Days until Pascha {}:"),
                    std::string(m_input_year_text->GetValue())));
    m_output_text->SetLabel(std::to_string(days.value));
  } // wxGuiView::update(Days)

  void wxGuiView::update(std::string_view message)
  {
    wxMessageDialog dialog(this, message.data(), "Error", wxOK | wxICON_ERROR);
    dialog.ShowModal();
  } // wxGuiView::update(std::string_view)

  std::string wxGuiView::formatDate(const Date& date) const
  {
    return fmt::format(fmt::runtime("{0}{3}{1}{3}{2}"), date.month, date.day,
                       date.year, m_date_separator);
  } // wxGuiView::formatDate(const Date&)

  void wxGuiView::onCalculate(wxCommandEvent & evt)
  {
    CalculationOptions options{};

    // Get calculation method
    if (m_julian_calculation_button->GetValue()) {
      options.calculation_method = e_calculation_method::julian;
    } else if (m_gregorian_calculation_button->GetValue()) {
      options.calculation_method = e_calculation_method::gregorian;
    }

    // Get target output
    switch (m_target_output_combobox->GetSelection()) {
      case 0: options.target_output = e_target_output::pascha; break;
      case 1: options.target_output = e_target_output::weeksBetween; break;
      case 2: options.target_output = e_target_output::daysUntil; break;
      case 3: options.target_output = e_target_output::meatfare; break;
      case 4: options.target_output = e_target_output::cheesefare; break;
      case 5: options.target_output = e_target_output::ashWednesday; break;
      case 6: options.target_output = e_target_output::midfeastPentecost; break;
      case 7: options.target_output = e_target_output::leavetakingPascha; break;
      case 8: options.target_output = e_target_output::ascension; break;
      case 9: options.target_output = e_target_output::pentecost; break;
    }

    // Get output calendar
    if (m_julian_calendar_button->GetValue()) {
      options.output_calendar = e_output_calendar::julian;
    } else if (m_gregorian_calendar_button->GetValue()) {
      options.output_calendar = e_output_calendar::gregorian;
    } else if (m_revised_julian_calendar_button->GetValue()) {
      options.output_calendar = e_output_calendar::rev_julian;
    }

    // Get the options
    if (m_byzantine_year_checkbox->GetValue()) {
      options.options.push_back(e_output_option::byzantine);
    }

    // Get the input year
    try {
      options.year = std::stoll(std::string(m_input_year_text->GetValue()));
    } catch (std::invalid_argument& e) {
      update("Invalid year");
      evt.Skip();
      return;
    } catch (std::out_of_range& e) {
      update("Year out of range");
      evt.Skip();
      return;
    }

    // TODO: FIXME

    // try {
    //   update(Days(34));
    //   mainSizer->Layout();
    // } catch (...) {
    //   std::exception_ptr p = std::current_exception();
    //     std::cout <<(p ? p.__cxa_exception_type()->name() : "null") <<
    //     std::endl;
    // }
    m_controller->calculate(options);
    mainSizer->Layout();
    evt.Skip();
  } // wxGuiView::onCalculate(wxCommandEvent&)

} // namespace pascha
