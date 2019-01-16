#pragma once
#include <SDL.h>
#include "tetris/headers/tetromino.h"

class Board {
public:
  Board(int heightBound);
  ~Board();

  void render(SDL_Renderer* renderer);
  bool shiftActiveTetromino(int x, int y);
  bool rotateActiveTetromino();
  void generateNewActiveTetromino();
  void generateNewActiveTetromino(Shape shape);
  void destroyActiveTetromino();

  int getWidth() const;
  int getHeight() const;
  int getGridUnitPixels() const;

  void tick(uint deltaTime);

  void printGrid();

private:
  bool isValidMove(Tetromino* tetromino, int xDelta, int yDelta);
  bool boundsCheck(Cell* cell, int xDelta, int yDelta);
  bool collisionCheck(Cell* cell, int xDelta, int yDelta);
  Tetromino* spawnRandomTetromino();
  void placeActiveTetromino();
  std::vector<int> findFilledRows();
  void clearRow(const int row);
  void shiftDown(const int row);
  bool isFilledRow(std::vector<Cell*>& row) const;

  SDL_Rect board;
  const int GRID_WIDTH = 10;
  const int GRID_HEIGHT = 20;
  const int SPAWN_ROWS = 4;
  int gridUnitPixels;
  Tetromino* activeTetromino;
  std::vector<Tetromino*> placedTetrominos;
  std::vector<std::vector<Cell*>> grid;

  int dropRate = 1000;
  int timeSinceLastDrop = 0;
};