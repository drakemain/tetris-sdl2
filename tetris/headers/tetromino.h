#pragma once
#include "tetris/headers/cell.h"
#include <vector>
#include <map>

enum class Shape {
  I,
  J,
  L,
  O,
  S,
  T,
  Z
};

class Tetromino {
public:
  // Constructor; Needs render target
  Tetromino(SDL_Renderer* renderer, Shape shape, int cellSize);
  // Delete each cell and vector container
  ~Tetromino();

  // Renders the tetromino's cells
  void render(SDL_Renderer* renderer);
  // Adjusts the position of each of the cells
  void shift(int gridUnitsX, int gridUnitsY);

private:
  // Initializes the container for the cell pointers
  void initCells(SDL_Renderer* renderer, std::array<std::array<Uint8, 4>, 4> shapeMatrix, int size);
  // Maps Uint8 to RGB struct
  SDL_Color getColor(Uint8);

private:
  // Pointers to the tetromino's cells
  std::vector<std::vector<Cell*>*> cellContainer;
};