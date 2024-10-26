#include "Window.hpp"
#include "Button.hpp"
#include <iostream>

namespace APP_NAME {

const std::vector<SDL_Keycode> key_list = {
    SDLK_1, SDLK_2, SDLK_3, SDLK_4, SDLK_5, SDLK_6, SDLK_7, SDLK_8,
    SDLK_q, SDLK_w, SDLK_e, SDLK_r, SDLK_t, SDLK_y, SDLK_u, SDLK_i,
    SDLK_a, SDLK_s, SDLK_d, SDLK_f, SDLK_g, SDLK_h, SDLK_j, SDLK_k,
    SDLK_z, SDLK_x, SDLK_c, SDLK_v, SDLK_b, SDLK_n, SDLK_m, SDLK_COMMA};

Window::Window() : window(nullptr), renderer(nullptr), config() {
  SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "2");
  window = SDL_CreateWindow(
      app_name, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280, 720,
      SDL_WINDOW_RESIZABLE | SDL_WINDOW_HIDDEN | SDL_WINDOW_ALLOW_HIGHDPI);
  renderer = SDL_CreateRenderer(
      window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
  SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
  SDL_RenderSetLogicalSize(renderer, 1280, 720);
  SDL_RenderSetVSync(renderer, 1);
  SDL_SetHint(SDL_HINT_MOUSE_TOUCH_EVENTS, "1");
  SDL_EventState(SDL_DROPFILE, SDL_ENABLE);
  // 足りないなら勝手に埋める
  auto &toml = this->config.getToml();
  if (!toml["files"].is_array())
    toml.erase("files");
  if (!toml.contains("files"))
    toml.emplace("files", toml::array());
  auto &arr = *toml["files"].as_array();
  int n = std::max(32 - arr.size(), 0UL);
  for (int i = 0; i < n; i++) {
    arr.push_back("");
  }
  Mix_AllocateChannels(32);
}

Window::~Window() {
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
}

void Window::Run() {
  SoundDeviceDescription sdd;
  uint16_t format;
  Mix_QuerySpec(&sdd.freq, &format, &sdd.channels);
  switch (format) {
  case AUDIO_S32MSB:
  case AUDIO_S32LSB:
  case AUDIO_F32MSB:
  case AUDIO_F32LSB:
    sdd.bytes = 4;
    break;
  case AUDIO_S16LSB:
  case AUDIO_S16MSB:
  case AUDIO_U16LSB:
  case AUDIO_U16MSB:
    sdd.bytes = 2;
    break;
  case AUDIO_S8:
  case AUDIO_U8:
    sdd.bytes = 1;
    break;
  }

  std::vector<Button> but;
  SDL_Rect rect1 = {0, 0, 160, 160};

  uint64_t next = SDL_GetTicks64();

  for (int i = 0; i < 4; i++)
    for (int j = 0; j < 8; j++) {
      rect1.x = j * 160;
      rect1.y = i * 160 + 80;
      but.emplace_back(rect1, key_list[i * 8 + j], i * 8 + j, &sdd);
    }

  auto &toml = this->config.getToml();

  if (auto files = toml["files"].as_array()) {
    for (int i = 0; i < std::min(files->size(), 16UL); i++) {
      if (files[0][i].is_string())
        but[i].Load(files[0][i].as_string()->get().c_str());
    }
  }



  SDL_ShowWindow(window);
  bool quit = false;
  SDL_Event event;
  while (!quit) {
    while (SDL_PollEvent(&event)) {
      switch (event.type) {
      case SDL_QUIT:
        quit = true;
        break;
      case SDL_KEYDOWN:
        for (int i = 0; i < but.size(); i++) {
          if (but[i].Pushed(event.key.keysym))
            break;
        }
        break;
      case SDL_FINGERDOWN: {
        if (SDL_GetTouchDeviceType(event.tfinger.touchId) !=
            SDL_TOUCH_DEVICE_DIRECT)
          break;
        int w, h;
        float x, y;
        SDL_GetWindowSize(window, &w, &h);
        SDL_RenderWindowToLogical(renderer, event.tfinger.x * w,
                                  event.tfinger.y * h, &x, &y);
        for (int i = 0; i < but.size(); i++) {
          if (but[i].Touched(x, y))
            break;
        }
        break;
      }
      case SDL_DROPFILE: {
        char *ch = event.drop.file;
        int x = 0, y = 0;
        SDL_GetMouseState(&x, &y);
        for (int i = 0; i < but.size(); i++) {
          if (but[i].Droped(x, y, ch)) {
            auto &files = *toml["files"].as_array();
            files.replace(files.cbegin() + i, std::string(ch));
            break;
          }
        }
        SDL_free(ch);
        break;
      }
      }
    }
    auto now = SDL_GetTicks64();
    if (next < now) {
      SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0x00);
      SDL_RenderClear(renderer);

      uint64_t tick = SDL_GetTicks64();
      for (int i = 0; i < but.size(); i++) {
        but[i].Draw(renderer, tick);
      }
      SDL_RenderPresent(renderer);

      // 20FPSでいいでしょ
      next += 50;
    } else {
      SDL_Delay(5);
    }
  }
  SDL_HideWindow(window);
}
} // namespace APP_NAME
