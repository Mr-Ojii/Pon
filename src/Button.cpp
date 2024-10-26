#include "Button.hpp"

namespace APP_NAME {
Button::Button(const SDL_Rect &rect, const SDL_Keycode &code, const int i,
               SoundDeviceDescription *sdd)
    : chunk(nullptr), pos(0, 0) {
  this->rect = rect;
  this->fill_rect = this->rect;
  this->fill_rect.x += 10;
  this->fill_rect.y += 10;
  this->fill_rect.w -= 20;
  this->fill_rect.h -= 20;
  this->code = code;
  this->i = i;
  this->sdd = sdd;
}
Button::~Button() {
  Mix_FreeChunk(this->chunk);
  this->chunk = nullptr;
}
void Button::Draw(SDL_Renderer *renderer, const uint64_t tick) const {
  if (this->chunk != nullptr)
    SDL_SetRenderDrawColor(renderer, 0xff, 0xff, 0xff, 0xff);
  else
    SDL_SetRenderDrawColor(renderer, 0x66, 0x66, 0x66, 0xff);
  SDL_RenderDrawRect(renderer, &this->rect);

  if (this->chunk == nullptr)
    return;

  SDL_SetRenderDrawColor(renderer, 0xff, 0xff, 0xff, 0xff);
  SDL_Rect fill_rect_tmp = fill_rect;
  if (tick <= pos.stop) {
    double ratio = (pos.len - (pos.stop - tick)) / (double)pos.len;
    int c = fill_rect_tmp.w * ratio;
    fill_rect_tmp.x += c;
    fill_rect_tmp.w -= c;
    SDL_RenderFillRect(renderer, &fill_rect_tmp);
  }
}
void Button::Play() {
  if (this->chunk == nullptr)
    return;
  Mix_PlayChannel(i, this->chunk, false);
  uint64_t msec =
      chunk->alen / (sdd->freq * sdd->channels * sdd->bytes / 1000.0);
  pos.len = msec;
  pos.stop = SDL_GetTicks64() + msec;
}
void Button::Stop() {
  Mix_HaltChannel(i);
  pos.stop = SDL_GetTicks64();
}
bool Button::Droped(const float x, const float y, const char *path) {
  if (rect.x <= x && rect.x + rect.w >= x && rect.y <= y &&
      rect.y + rect.h >= y) {
    return this->Load(path);
  }
  return false;
}
bool Button::Touched(const float x, const float y) {
  if (rect.x <= x && rect.x + rect.w >= x && rect.y <= y &&
      rect.y + rect.h >= y) {
    if (chunk != nullptr)
      this->Play();
    return true;
  }
  return false;
}
bool Button::Pushed(const SDL_Keysym keysym) {
  if (keysym.sym != this->code)
    return false;
  if ((keysym.mod & (KMOD_LSHIFT | KMOD_RSHIFT)) == 0) {
    this->Play();
  } else {
    this->Stop();
  }
  return true;
}
bool Button::Load(const char *path) {
  Mix_Chunk *chu = Mix_LoadWAV(path);
  if (!chu)
    return false;
  this->Stop();
  Mix_FreeChunk(this->chunk);
  this->chunk = chu;
  return true;
}
} // namespace APP_NAME
