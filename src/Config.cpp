#include "Config.hpp"
#include <algorithm>
#include <filesystem>
#include <fstream>
#include <iostream>

namespace APP_NAME {
Config::Config() {
  char *base = SDL_GetBasePath();
  std::filesystem::path toml_path = std::filesystem::path(base) / "config.toml";
  SDL_free(base);
  if (std::filesystem::exists(toml_path))
    toml = toml::parse_file(toml_path.string());
}
Config::~Config() {
  char *base = SDL_GetBasePath();
  std::filesystem::path toml_path = std::filesystem::path(base) / "config.toml";
  SDL_free(base);
  std::ofstream ofs(toml_path);
  if (!ofs)
    return;
  ofs << toml::toml_formatter{toml} << std::endl;
  ofs.close();
}
} // namespace APP_NAME
