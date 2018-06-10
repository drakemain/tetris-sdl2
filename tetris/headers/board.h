#pragma once
#include <SDL.h>
#include "tetris/headers/tetromino.h"

class Board {
public:
  Board(int heightBound);
  ~Board();
  
  void placeTetromino(Tetromino* tetromino);
  void render(SDL_Renderer* renderer);

  int getWidth() const;
  int getHeight() const;
  int getGridUnitPixels() const;

private:
  SDL_Rect board;
  const int GRID_WIDTH = 10;
  const int GRID_HEIGHT = 20;
  int gridUnitPixels;
  std::vector<Tetromino*> placedTetrominos;
  std::vector<std::vector<Cell*>> grid;
};