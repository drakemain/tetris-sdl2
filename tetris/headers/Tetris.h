#pragma once
#include "tetris/headers/tetromino.h"
#include "tetris/headers/board.h"
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
  void render();
  void keyboardHandler(SDL_Keycode key);
  void initGameBoard();

private:
  SDL_Window* window;
  SDL_Renderer* renderer;
  Board* board;

  const int WINDOW_WIDTH = 1920;
  const int WINDOW_HEIGHT = 1080;
};