#pragma once
#include "tetris/headers/tetromino.h"
#include <SDL.h>

class Tetris {
public:
  // SDL Initialization
  bool init();
  // Contains game loop
  void run();
  // Cleanup assets
  void cleanup();

  /** Getters **/
  SDL_Window* getWindow() const;
  SDL_Renderer* getRenderer() const;

private:
  void render(Tetromino& tetromino);

private:
  SDL_Window* window;
  SDL_Renderer* renderer;

  SDL_Rect gameBoard;

  const int WIDTH = 640;
  const int HEIGHT = 480;

  const int gridUnitSize = 50;
};