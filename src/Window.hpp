#pragma once
#include "Config.hpp"
#include "Const.hpp"
#include "Depends.hpp"
#include "Midi.hpp"

namespace APP_NAME {
class Window final {
private:
  SDL_Window *window;
  SDL_Renderer *renderer;
  Config config;
  Midi midi;

public:
  Window();
  ~Window();
  void Run();
};
} // namespace APP_NAME
