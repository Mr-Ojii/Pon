#pragma once
#include "Const.hpp"
#include "Depends.hpp"

namespace APP_NAME {
struct PlayPos {
  uint64_t len;
  uint64_t stop;
  PlayPos(uint64_t len, uint64_t stop) {
    this->len = len;
    this->stop = stop;
  };
};
} // namespace APP_NAME
