#ifdef WIN32
#define SDL_MAIN_HANDLED
#endif

#include "Depends.hpp"
#include "Window.hpp"
#include <cstdlib>
#include <filesystem>
#include <format>
#include <iostream>

int main(int argc, char* argv[]) {
  {
    char *base = SDL_GetBasePath();
    std::filesystem::current_path(base);
    SDL_free(base);
  }
  SDL_SetHint(SDL_HINT_TRACKPAD_IS_TOUCH_ONLY, "1");
  int sdl_flags =
      SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_EVENTS | SDL_INIT_TIMER;
  if (SDL_Init(sdl_flags) != 0) {
    SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, app_name,
                             "Failed to initialize SDL...", nullptr);
    return 1;
  }
  std::atexit(SDL_Quit);

  int mix_flags = MIX_INIT_MP3 | MIX_INIT_OGG | MIX_INIT_OPUS | MIX_INIT_FLAC;
  if (Mix_Init(mix_flags) != mix_flags) {
    SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, app_name,
                             "Failed to initialize SDL_mixer...", nullptr);
    return 1;
  }
  std::atexit(Mix_Quit);
  if (Mix_OpenAudioDevice(
          48000, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024, nullptr,
          SDL_AUDIO_ALLOW_FREQUENCY_CHANGE | SDL_AUDIO_ALLOW_CHANNELS_CHANGE)) {
    SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, app_name,
                             "Failed to open audio device...", nullptr);
    return 1;
  }

  try {
    APP_NAME::Window win;
    win.Run();
  } catch (const toml::parse_error &e) {
    SDL_ShowSimpleMessageBox(
        SDL_MESSAGEBOX_ERROR, app_name,
        std::format("Exception has occured.\nFailed to parse toml.\n({}, {})",
                    e.what(), e.source().path->c_str())
            .c_str(),
        nullptr);
  } catch (const std::exception &e) {
    SDL_ShowSimpleMessageBox(
        SDL_MESSAGEBOX_ERROR, app_name,
        std::format("Exception has occured.\nsorry...\n({})", e.what()).c_str(),
        nullptr);
  } catch (...) {
    SDL_ShowSimpleMessageBox(
        SDL_MESSAGEBOX_ERROR, app_name,
        std::format("Exception has occured.\nsorry...\n").c_str(), nullptr);
  }
  Mix_CloseAudio();
  return 0;
}
