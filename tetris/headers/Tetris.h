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
  void render();
  void keyboardHandler(SDL_Keycode key);
  void placeActiveTetromino();
  void generateNewActiveTetromino();
  void initGameBoard();

private:
  SDL_Window* window;
  SDL_Renderer* renderer;
  SDL_Rect gameBoard;
  Tetromino* activeTetromino;
  std::vector<Tetromino*> placedTetrominos;

  const int WINDOW_WIDTH = 1920;
  const int WINDOW_HEIGHT = 1080;

  const int BOARD_GRID_WIDTH = 10;
  const int BOARD_GRID_HEIGHT = 20;

  int gridUnitSize;
};