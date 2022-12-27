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
