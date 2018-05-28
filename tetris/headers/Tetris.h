#pragma once
#include <SDL.h>

class Tetris {
public:
  bool init();
  void run();
  void cleanup();

  SDL_Window* getWindow() const;
  SDL_Renderer* getRenderer() const;

private:
  void render();
  

private:
  SDL_Window* window;
  SDL_Renderer* renderer;

  const int WIDTH = 640;
  const int HEIGHT = 480;
};