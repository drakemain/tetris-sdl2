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

private:
  SDL_Window* window;
  SDL_Renderer* renderer;
  SDL_Rect gameBoard;
  Tetromino* activeTetromino;
  std::vector<Tetromino*> placedTetrominos;

  const int WIDTH = 640;
  const int HEIGHT = 480;

  const int gridUnitSize = 50;


  void keyboardHandler(SDL_Keycode key);
  void placeActiveTetromino();
  void generateNewActiveTetromino();
};