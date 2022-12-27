#ifndef PASCHA_CONFIG_IO_H
#define PASCHA_CONFIG_IO_H

#include "wx/filename.h"
#include "wx/string.h"

namespace pascha
{

struct Configuration {
  wxString pascha_name;
  wxString date_format;
  wxString date_separator;
}; // struct Configuration

const wxString config_file_name{"pascha-gui.conf"};

wxFileName configFile();
Configuration readConfigFile();

} // namespace pascha
#endif // !PASCHA_CONFIG_IO_H
