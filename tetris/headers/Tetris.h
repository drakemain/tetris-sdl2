#pragma once
#include "tetris/headers/tetromino.h"
#include "tetris/headers/board.h"
#include "tetris/headers/input.h"
#include "tetris/headers/Base.h"
#include <vector>
#include <SDL.h>

class Tetris : Base {
public:
  Tetris(){};
  Tetris(bool devMode): devMode(devMode){};
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
  bool devMode = false;

  const int WINDOW_WIDTH = 1280;
  const int WINDOW_HEIGHT = 1024;
};