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

#include "config_io.h"

#include <wx/stdpaths.h>
#include <wx/textfile.h>

#include <iostream>

namespace
{

using namespace pascha;

void processLine(Configuration& config, wxString line)
{
  if (line.StartsWith("pascha_name")) {
    config.pascha_name = line.AfterFirst(' ');
  } else if (line.StartsWith("date_format")) {
    config.date_format = line.AfterFirst(' ');
  } else if (line.StartsWith("date_separator")) {
    config.date_separator = line.AfterFirst(' ');
  }
} // processLine()

} // anonymous namespace

namespace pascha
{

wxFileName configFile()
{
  wxString config_file_path{wxStandardPaths::Get().GetUserConfigDir()};
  config_file_path += wxFileName::GetPathSeparator();

  // If path starts with /home/username, then it is a Linux path
  if (config_file_path.StartsWith("/home/")) { config_file_path += ".config/"; }

  wxString config_full_path{config_file_path + config_file_name};

  wxTextFile file{config_full_path};

  if (!file.Exists()) {
    try {
      wxFileName::Mkdir(config_file_path, wxS_DIR_DEFAULT, wxPATH_MKDIR_FULL);
    } catch (...) {
      std::cerr << "Error creating config directory: " + config_full_path;
      return wxFileName{};
    }
    if (!file.Create()) {
      std::cerr << "Error creating config file: " + config_full_path;
      return wxFileName{};
    } else {
      file.Close();
    }
  }

  return wxFileName{config_full_path};
} // configFile()

Configuration readConfigFile()
{
  Configuration config{};

  wxFileName config_file{configFile()};
  if (!config_file.FileExists()) { return config; }

  wxTextFile file{};
  file.Open(config_file.GetFullPath());
  if (!file.IsOpened()) {
    std::cerr << "Error opening config file: " + config_file.GetFullPath();
    return config;
  }

  try {
    wxString line{file.GetFirstLine()};
    processLine(config, line);
    while (!file.Eof()) {
      line = file.GetNextLine();
      processLine(config, line);
    }
  } catch (...) {
    std::cerr << "Error reading config file: " + config_file.GetFullPath();
  }

  file.Close();

  return config;
} // readConfigFile()

} // namespace pascha
