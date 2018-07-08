#include "tetris/headers/Base.h"
#include <iostream>

SDL_Renderer* Base::renderer = nullptr;
SDL_Window* Base::window = nullptr;
int Base::WINDOW_WIDTH = 480;
int Base::WINDOW_HEIGHT = 640;

SDL_Window* Base::getWindow() const {
  return this->window;
}

SDL_Renderer* Base::getRenderer() const {
  return this->renderer;
}

void Base::setWindow(SDL_Window* window) {
  this->window = window;
}

void Base::setRenderer(SDL_Renderer* renderer) {
  this->renderer = renderer;
}

void Base::destroyWindow() {
  SDL_DestroyWindow(this->window);
}

void Base::clearRenderer() {
  SDL_RenderClear(this->renderer);
}