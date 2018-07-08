#pragma once
#include "tetris/headers/tetromino.h"
#include "tetris/headers/board.h"
#include "tetris/headers/input.h"
#include "tetris/headers/Base.h"
#include <SDL.h>

class Tetris : Base {
public:
  // SDL Initialization
  bool init();
  // Contains game loop
  void run();
  // Cleanup assets
  void cleanup();

private:
  void render();
  void keyboardHandler(SDL_Keycode key);
  void initGameBoard();

private:
  Board* board;
  Input input;

  const int WINDOW_WIDTH = 1280;
  const int WINDOW_HEIGHT = 1024;
};