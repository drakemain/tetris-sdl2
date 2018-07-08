#pragma once
#include <SDL.h>

class Base {
protected:
  SDL_Window* getWindow() const;
  SDL_Renderer* getRenderer() const;

  void setWindow(SDL_Window* window);
  void setRenderer(SDL_Renderer* renderer);

  void destroyWindow();
  void clearRenderer();

private:
  static SDL_Renderer* renderer;
  static SDL_Window* window;
  static int WINDOW_WIDTH;
  static int WINDOW_HEIGHT;
};