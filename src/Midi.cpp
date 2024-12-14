#include "Midi.hpp"

namespace APP_NAME {
Midi::Midi() {
  for (int i = 0; i < top.getPortCount(); i++) {
    auto &midi = midi_in.emplace_back();
    midi.openPort(i);
    midi.setCallback(func, this);
  }
}
Midi::~Midi() {
  for (auto &midi : midi_in) {
    midi.cancelCallback();
    midi.closePort();
  }
}
bool Midi::empty() {
  std::lock_guard<std::mutex>(this->mtx);
  return this->queue.empty();
}
uint8_t Midi::pop() {
  std::lock_guard<std::mutex>(this->mtx);
  uint8_t u = this->queue.front();
  this->queue.pop();
  return u;
}
} // namespace APP_NAME
