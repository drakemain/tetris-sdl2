#pragma once
#include <SDL.h>
#include "tetris/headers/tetromino.h"

class Board {
public:
  Board(int heightBound, int horizontalPosition);
  ~Board();

  void render(SDL_Renderer* renderer);
  bool shiftActiveTetromino(int x, int y);
  bool rotateActiveTetromino();
  void generateNewActiveTetromino();
  void generateNewActiveTetromino(Shape shape);
  void destroyActiveTetromino();

  void setBackgroundColor(const SDL_Color);

  void createGhost();

  int getWidth() const;
  int getHeight() const;
  int getGridUnitPixels() const;
  bool checkHasLost() const;
  uint getDeltaPoints();

  void tick(uint deltaTime);

  void reset();

  void printGrid();

private:
  void adjustGhost(int x);
  void reduceDropRate();
  bool isValidMove(Tetromino* tetromino, int xDelta, int yDelta);
  bool boundsCheck(Cell* cell, int xDelta, int yDelta);
  bool boundsCheck(Tetromino&, int xDelta, int yDelta);
  bool collisionCheck(Cell* cell, int xDelta, int yDelta);
  Tetromino* spawnRandomTetromino();
  void placeActiveTetromino();
  std::vector<int> findFilledRows();
  void clearRow(const int row);
  void shiftDown(const int row);
  bool isFilledRow(std::vector<Cell*>& row) const;
  void cleanup();

  SDL_Rect board;
  SDL_Color background = {255, 255, 255, 100};
  bool hasLost = false;
  const int GRID_WIDTH = 10;
  const int GRID_HEIGHT = 20;
  const int SPAWN_ROWS = 4;
  int gridUnitPixels;
  Tetromino* activeTetromino = nullptr;
  Tetromino* dropGhost = nullptr;
  std::vector<Tetromino*> placedTetrominos;
  std::vector<std::vector<Cell*>> grid;

  int dropRate = 1000;
  int timeSinceLastDrop = 0;
  uint deltaPoints;
};