#pragma once
#include "Const.hpp"
#include "Depends.hpp"
#include <list>
#include <mutex>
#include <queue>

namespace APP_NAME {
class Midi {
private:
  RtMidiIn top;
  std::list<RtMidiIn> midi_in;
  std::mutex mtx;
  std::queue<uint8_t> queue;

  static void func( double timeStamp, std::vector<unsigned char> *message, void *userData ) {
    auto midi = reinterpret_cast<Midi*>(userData);
    std::lock_guard<std::mutex>(midi->mtx);

    for (int i = 0; i < message->size() / 3; i++) {
      uint8_t mess = message->at(i * 3);
      if (0x90 <= mess && mess <= 0x9f)
        midi->queue.push(message->at(i * 3 + 1));
    }
  }
public:
  Midi();
  ~Midi();
  bool empty();
  uint8_t pop();
};
} // namespace APP_NAME
