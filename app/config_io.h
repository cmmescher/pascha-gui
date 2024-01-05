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
