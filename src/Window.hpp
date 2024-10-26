#pragma once
#include "Config.hpp"
#include "Const.hpp"
#include "Depends.hpp"

namespace APP_NAME {
class Window final {
private:
  SDL_Window *window;
  SDL_Renderer *renderer;
  Config config;

public:
  Window();
  ~Window();
  void Run();
};
} // namespace APP_NAME
