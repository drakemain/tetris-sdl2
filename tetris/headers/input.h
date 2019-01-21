#pragma once
#include <SDL.h>

class Input {
public:
  // poll the event queue. returns true if there is a pending event
  bool poll();

  // determine the type of the last polled event.
  Uint32 getType() const;

  SDL_Keycode getKeyCode() const;

private:
  SDL_Event event;
};