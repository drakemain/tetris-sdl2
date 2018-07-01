#include "tetris/headers/input.h"

bool Input::poll() {
  if (SDL_PollEvent(&this->event) > 0) {
    return true;
  } else {
    return false;
  }
}

Uint32 Input::getType() const {
  return this->event.type;
}

SDL_Keycode Input::getKeyCode() const {
  return this->event.key.keysym.sym;
}