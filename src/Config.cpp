#include "Config.hpp"
#include <filesystem>
#include <fstream>
#include <iostream>
#include <algorithm>

namespace APP_NAME {
Config::Config() {
  std::filesystem::path toml_path =
      std::filesystem::path(SDL_GetBasePath()) / "config.toml";
  if (std::filesystem::exists(toml_path))
    toml = toml::parse_file(toml_path.string());
}
Config::~Config() {
  std::filesystem::path toml_path =
      std::filesystem::path(SDL_GetBasePath()) / "config.toml";
  std::ofstream ofs(toml_path);
  if (!ofs)
    return;
  ofs << toml::toml_formatter{toml} << std::endl;
  ofs.close();
}
} // namespace APP_NAME
