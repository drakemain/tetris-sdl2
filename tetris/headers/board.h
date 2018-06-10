#pragma once
#include <SDL.h>
#include "tetris/headers/tetromino.h"

class Board {
public:
  Board(int heightBound, SDL_Renderer* renderer, Uint8 r, Uint8 g, Uint8 b, Uint8 a);
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
  SDL_Texture* background;
  int gridUnitPixels;
  std::vector<Tetromino*> placedTetrominos;
};