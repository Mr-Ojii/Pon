#pragma once
#include "Const.hpp"
#include "Depends.hpp"
#include "PlayPos.hpp"
#include "SoundDeviceDescription.hpp"

namespace APP_NAME {

class Button final {
private:
  SDL_Rect rect;
  SDL_Rect fill_rect;
  SDL_Keycode code;
  Mix_Chunk *chunk;
  PlayPos pos;
  int i;
  SoundDeviceDescription* sdd;
  void Play();
  void Stop();

public:
  Button(const SDL_Rect& rect, const SDL_Keycode& code, const int i, SoundDeviceDescription* device);
  ~Button();
  void Draw(SDL_Renderer*, const uint64_t) const;
  bool Droped(const float, const float, const char*);
  bool Touched(const float, const float);
  bool Pushed(const SDL_Keysym code);
  bool Load(const char* path);
};

} // namespace APP_NAME
