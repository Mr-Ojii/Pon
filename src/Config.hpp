#pragma once
#include "Const.hpp"
#include "Depends.hpp"

namespace APP_NAME {
class Config final {
private:
  toml::table toml;

public:
  Config();
  ~Config();
  toml::table& getToml() { return toml; }
};
} // namespace APP_NAME
