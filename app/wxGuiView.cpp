#include "wxGuiView.h"

#include "config_io.h"
#include "pascha/calculation_options.h"

#include <fmt/core.h>
#include <wx/stdpaths.h>
#include <wx/textfile.h>
#include <wx/wrapsizer.h>

#include <algorithm>
#include <chrono>
#include <ctime>
#include <string>
#include <string_view>

namespace pascha
{
wxGuiView::wxGuiView(IController& controller, ICalculatorModel& model,
                     std::string_view pascha_name, DateFormat date_format,
                     std::string_view date_separator)
    : wxFrame{nullptr, wxID_ANY, "Pascha Calculator", wxDefaultPosition,
              wxSize(550, 400)},
      m_controller{&controller},
      m_model{&model},
      m_pascha_name{pascha_name},
      m_date_format{date_format},
      m_date_separator{date_separator},
      m_pascha_name_choices{{"Pascha", "Easter"}},
      m_date_format_choices{{"YMD", "MDY", "DMY"}}
{
  m_model->addObserver(*this);
  m_controller->addView(*this);

  m_menu_bar = new wxMenuBar();
  this->SetMenuBar(m_menu_bar);

  wxMenu* settings_menu = new wxMenu;
  settings_menu->Append(id_pascha_name_menu_item, "Pascha Name");
  settings_menu->Append(id_date_format_menu_item, "Date Format");
  settings_menu->Append(id_date_separator_menu_item, "Date Separator");
  settings_menu->Append(id_save_preferences_menu_item, "Save Preferences");

  m_menu_bar->Append(settings_menu, "Settings");

  m_main_sizer = new wxBoxSizer(wxVERTICAL);

  wxScrolledWindow* sw = new wxScrolledWindow(this, wxID_ANY, wxDefaultPosition,
                                              wxDefaultSize, wxVSCROLL);
  m_main_sizer->Add(sw, 1, wxEXPAND | wxALL, 5);

  wxBoxSizer* sw_sizer = new wxBoxSizer(wxVERTICAL);

  m_header = new wxStaticText(sw, wxID_ANY, m_pascha_name + " Calculator",
                              wxDefaultPosition, wxDefaultSize, wxALIGN_CENTRE);
  m_header->SetFont(wxFont(18, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL,
                           wxFONTWEIGHT_BOLD, false));
  sw_sizer->Add(m_header, 0, wxALL | wxEXPAND, 5);

  wxWrapSizer* calculation_method_sizer = new wxWrapSizer(wxHORIZONTAL);
  m_calculation_method_label =
      new wxStaticText(sw, wxID_ANY, "Calculation Method:");
  calculation_method_sizer->Add(m_calculation_method_label, 0, wxALL, 5);
  m_julian_calculation_button = new wxRadioButton(
      sw, wxID_ANY, "Julian", wxDefaultPosition, wxDefaultSize, wxRB_GROUP);
  calculation_method_sizer->Add(m_julian_calculation_button, 0, wxALL, 5);
  m_gregorian_calculation_button = new wxRadioButton(sw, wxID_ANY, "Gregorian");
  calculation_method_sizer->Add(m_gregorian_calculation_button, 0, wxALL, 5);
  m_julian_calculation_button->SetValue(true);
  sw_sizer->Add(calculation_method_sizer, 0, wxALL | wxEXPAND, 5);

  wxWrapSizer* target_output_sizer = new wxWrapSizer(wxHORIZONTAL);
  m_target_output_label = new wxStaticText(sw, wxID_ANY, "Target Output:");
  target_output_sizer->Add(m_target_output_label, 0, wxALL, 5);
  m_target_output_combobox =
      new wxComboBox(sw, wxID_ANY, "Pascha", wxDefaultPosition, wxDefaultSize,
                     0, nullptr, wxCB_READONLY);
  setTargetOutputChoices(m_target_output_combobox);
  m_target_output_combobox->SetSelection(0);
  target_output_sizer->Add(m_target_output_combobox, 0, wxALL, 5);
  sw_sizer->Add(target_output_sizer, 0, wxALL | wxEXPAND, 5);

  wxWrapSizer* calendar_sizer = new wxWrapSizer(wxHORIZONTAL);
  m_output_calendar_label = new wxStaticText(sw, wxID_ANY, "Output Calendar:");
  calendar_sizer->Add(m_output_calendar_label, 0, wxALL, 5);
  m_julian_calendar_button = new wxRadioButton(
      sw, wxID_ANY, "Julian", wxDefaultPosition, wxDefaultSize, wxRB_GROUP);
  calendar_sizer->Add(m_julian_calendar_button, 0, wxALL, 5);
  m_gregorian_calendar_button = new wxRadioButton(sw, wxID_ANY, "Gregorian");
  calendar_sizer->Add(m_gregorian_calendar_button, 0, wxALL, 5);
  m_revised_julian_calendar_button =
      new wxRadioButton(sw, wxID_ANY, "Revised Julian");
  calendar_sizer->Add(m_revised_julian_calendar_button, 0, wxALL, 5);
  m_julian_calendar_button->SetValue(true);
  sw_sizer->Add(calendar_sizer, 0, wxALL | wxEXPAND, 5);

  wxWrapSizer* options_sizer = new wxWrapSizer(wxHORIZONTAL);
  m_options_label = new wxStaticText(sw, wxID_ANY, "Options:");
  options_sizer->Add(m_options_label, 0, wxALL, 5);
  m_byzantine_year_checkbox = new wxCheckBox(sw, wxID_ANY, "Byzantine Year");
  options_sizer->Add(m_byzantine_year_checkbox, 0, wxALL, 5);
  sw_sizer->Add(options_sizer, 0, wxALL | wxEXPAND, 5);

  wxWrapSizer* input_year_sizer = new wxWrapSizer(wxHORIZONTAL);
  m_input_year_label = new wxStaticText(sw, wxID_ANY, "Input Year:");
  input_year_sizer->Add(m_input_year_label, 0, wxALL, 5);
  auto now{std::chrono::system_clock::now()};
  auto nowTime{std::chrono::system_clock::to_time_t(now)};
  auto currYear{std::localtime(&nowTime)->tm_year + 1900};
  wxString currYearStr{std::to_string(currYear)};
  m_input_year_text = new wxTextCtrl(sw, wxID_ANY, currYearStr);
  input_year_sizer->Add(m_input_year_text, 0, wxALL, 5);
  sw_sizer->Add(input_year_sizer, 0, wxALL | wxEXPAND, 5);

  m_calculate_button = new wxButton(sw, id_calculate_button, "Calculate");
  sw_sizer->Add(m_calculate_button, 0, wxALL | wxCENTER, 5);

  wxWrapSizer* output_sizer = new wxWrapSizer(wxHORIZONTAL);
  m_output_label = new wxStaticText(sw, wxID_ANY, "");
  output_sizer->Add(m_output_label, 0, wxALL, 5);
  m_output_text = new wxStaticText(sw, wxID_ANY, "");
  output_sizer->Add(m_output_text, 0, wxALL, 5);
  sw_sizer->Add(output_sizer, 0, wxALL | wxEXPAND, 5);

  sw->SetSizer(sw_sizer);
  sw->SetScrollRate(5, 5);
  sw_sizer->Layout();
  this->SetSizer(m_main_sizer);
  m_main_sizer->Layout();
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
  m_output_label->SetLabel(
      fmt::format(fmt::runtime("Weeks between Julian and Gregorian {} {}:"),
                  m_pascha_name, std::string(m_input_year_text->GetValue())));
  m_output_text->SetLabel(std::to_string(weeks.value));
} // wxGuiView::update(Weeks)

void wxGuiView::update(Days days)
{
  m_output_label->SetLabel(
      fmt::format(fmt::runtime("Days until {} {}:"), m_pascha_name,
                  std::string(m_input_year_text->GetValue())));
  m_output_text->SetLabel(std::to_string(days.value));
} // wxGuiView::update(Days)

void wxGuiView::update(std::string_view message)
{
  wxMessageDialog dialog(this, message.data(), "Error", wxOK | wxICON_ERROR);
  dialog.ShowModal();
} // wxGuiView::update(std::string_view)

void wxGuiView::onPaschaNameClicked(wxCommandEvent& evt)
{
  wxSingleChoiceDialog dialog(this, "Pascha Name", "Pascha Name", 2,
                              m_pascha_name_choices.data());
  auto it = std::find(m_pascha_name_choices.begin(),
                      m_pascha_name_choices.end(), m_pascha_name);
  if (it != m_pascha_name_choices.end()) {
    dialog.SetSelection(std::distance(m_pascha_name_choices.begin(), it));
  }
  auto selection = dialog.ShowModal();
  if (selection == wxID_CANCEL) {
    evt.Skip();
    return;
  }
  setPaschaName(dialog.GetStringSelection());
  evt.Skip();
} // wxGuiView::onPaschaNameClicked(wxCommandEvent&)

void wxGuiView::onDateFormatClicked(wxCommandEvent& evt)
{
  wxSingleChoiceDialog dialog(this, "Select date format", "Date Format", 3,
                              m_date_format_choices.data());
  auto it = std::find(m_date_format_choices.begin(),
                      m_date_format_choices.end(), getDateFormat());
  if (it != m_date_format_choices.end()) {
    dialog.SetSelection(std::distance(m_date_format_choices.begin(), it));
  }
  auto selection = dialog.ShowModal();
  if (selection == wxID_CANCEL) {
    evt.Skip();
    return;
  }
  setDateFormat(dialog.GetStringSelection());
  if (m_output_label->GetLabel() != "") {
    onCalculateClicked(evt);
  } else {
    evt.Skip();
  }
} // wxGuiView::onSettingsClick(wxCommandEvent&)

void wxGuiView::onSeparatorClicked(wxCommandEvent& evt)
{
  wxTextEntryDialog dialog(this, "Enter separator", "Separator",
                           m_date_separator);
  auto selection = dialog.ShowModal();
  if (selection == wxID_CANCEL) {
    evt.Skip();
    return;
  }
  setDateSeparator(dialog.GetValue());
  if (m_output_label->GetLabel() != "") {
    onCalculateClicked(evt);
  } else {
    evt.Skip();
  }
} // wxGuiView::onSeparatorClicked(wxCommandEvent&)

void wxGuiView::onSavePreferencesClicked(wxCommandEvent& evt)
{
  wxMessageDialog dialog(this, "Save preferences?", "Save preferences",
                         wxYES_NO | wxICON_QUESTION);
  auto selection = dialog.ShowModal();
  if (selection == wxID_YES) { writeConfigFile(); }
  evt.Skip();
}

void wxGuiView::onCalculateClicked(wxCommandEvent& evt)
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

  m_controller->calculate(options);
  m_main_sizer->Layout();
  evt.Skip();
} // wxGuiView::onCalculate(wxCommandEvent&)

void wxGuiView::setTargetOutputChoices(wxComboBox* combobox)
{
  combobox->Clear();
  combobox->Append(m_pascha_name);
  combobox->Append("Weeks between Julian and Gregorian " + m_pascha_name);
  combobox->Append("Days until " + m_pascha_name);
  combobox->Append("Meatfare");
  combobox->Append("Cheesefare");
  combobox->Append("Ash Wednesday");
  combobox->Append("Midfeast of Pentecost");
  combobox->Append("Leavetaking of " + m_pascha_name);
  combobox->Append("Ascension");
  combobox->Append("Pentecost");
}

void wxGuiView::setPaschaName(const wxString& name)
{
  m_pascha_name = name;
  refreshPaschaName();
} // wxGuiView::setPaschaName(std::string_view)

void wxGuiView::refreshPaschaName()
{
  // Refresh header
  m_header->SetLabel(m_pascha_name + " Calculator");
  m_header->Refresh();

  // Refresh target output choices
  auto selection = m_target_output_combobox->GetSelection();
  setTargetOutputChoices(m_target_output_combobox);
  m_target_output_combobox->SetSelection(selection);

  // Refresh output label

  std::string old_label = std::string(m_output_label->GetLabelText());
  auto found = old_label.find(m_pascha_name);
  if (found == std::string::npos && old_label != "") { // not found
    std::string old_pascha_name =
        m_pascha_name == "Pascha" ? "Easter" : "Pascha";
    std::string new_label =
        old_label.replace(old_label.find(old_pascha_name),
                          old_pascha_name.length(), m_pascha_name);
    m_output_label->SetLabelText(new_label);
    m_output_label->Refresh();
  }

  m_main_sizer->Layout();
} // wxGuiView::refreshPaschaName()

void wxGuiView::setDateFormat(const wxString& format)
{
  if (format == "YMD") {
    m_date_format = DateFormat::YMD;
  } else if (format == "MDY") {
    m_date_format = DateFormat::MDY;
  } else if (format == "DMY") {
    m_date_format = DateFormat::DMY;
  }
} // wxGuiView::setDateFormat(const wxString&)

const wxString wxGuiView::getDateFormat() const
{
  switch (m_date_format) {
    case DateFormat::YMD: return "YMD";
    case DateFormat::MDY: return "MDY";
    case DateFormat::DMY: return "DMY";
  }
  return "";
} // wxGuiView::getDateFormat() const

std::string wxGuiView::formatDate(const Date& date) const
{
  std::string format_string{};
  switch (m_date_format) {
    case DateFormat::YMD: format_string = "{0}{3}{1}{3}{2}"; break;
    case DateFormat::MDY: format_string = "{1}{3}{2}{3}{0}"; break;
    case DateFormat::DMY: format_string = "{2}{3}{1}{3}{0}"; break;
    default: format_string = "{0}{3}{1}{3}{2}"; break;
  }
  return fmt::format(fmt::runtime(format_string), date.year, date.month,
                     date.day, m_date_separator);
} // wxGuiView::formatDate(const Date&)

void wxGuiView::setDateSeparator(const wxString& separator)
{
  m_date_separator = separator;
} // wxGuiView::setDateSeparator(const wxString&)

void wxGuiView::writeConfigFile()
{
  wxFileName config_file{configFile()};

  if (!config_file.FileExists()) {
    update("Failed to write config file!");
    return;
  }

  wxTextFile file{};
  file.Open(config_file.GetFullPath());
  if (!file.IsOpened()) {
    update("Failed to write config file!");
    return;
  }
  // try writing to the config file
  try {
    file.Clear();
    file.AddLine("pascha_name: " + m_pascha_name);
    file.AddLine("date_format: " + getDateFormat());
    file.AddLine("date_separator: " + m_date_separator);
    file.Write();
    file.Close();
  } catch (...) {
    update("Failed to write config file!");
    file.Close();
    return;
  }

  wxMessageDialog dialog{this, "Config file written!", "Success",
                         wxOK | wxICON_INFORMATION};
  dialog.ShowModal();
} // wxGuiView::writeConfigFile()

} // namespace pascha

wxBEGIN_EVENT_TABLE(pascha::wxGuiView, wxFrame)
  EVT_MENU(id_pascha_name_menu_item, pascha::wxGuiView::onPaschaNameClicked)
  EVT_MENU(id_date_format_menu_item,
    pascha::wxGuiView::onDateFormatClicked)
  EVT_MENU(id_date_separator_menu_item,
    pascha::wxGuiView::onSeparatorClicked)
  EVT_MENU(id_save_preferences_menu_item,
    pascha::wxGuiView::onSavePreferencesClicked)
  EVT_BUTTON(id_calculate_button,
    pascha::wxGuiView::onCalculateClicked)
wxEND_EVENT_TABLE()
