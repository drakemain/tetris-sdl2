#pragma once
#include "tetris/headers/cell.h"
#include <vector>
#include <map>

typedef std::array<std::array<Uint8, 4>, 4> ShapeMatrix;

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
  bool shift(int gridUnitsX, int gridUnitsY, std::pair<int, int> bounds);
  // Rotate the cells within the matrix CW 90 degrees
  void rotate(SDL_Renderer* renderer);

  bool isWithinBounds(std::pair<int, int> positionDelta, std::pair<int, int> bounds);
  
  // Getters
  ShapeMatrix getShapeMatrix() const;

private:
  // Initializes the container for the cell pointers
  void initCells(SDL_Renderer* renderer, std::array<std::array<Uint8, 4>, 4> shapeMatrix, int size);
  // Maps Uint8 to RGB struct
  SDL_Color getColor(Uint8);
  // Finds the relative position within the matrix of bound (TOP, BOTTOM, LEFT, RIGHT)
  int getTopBound();
  int getBottomBound();
  int getLeftBound();
  int getRightBound();

private:
  // Pointers to the tetromino's cells
  std::vector<Cell*> cells;
  // Matrix representing tetromino shape
  ShapeMatrix shapeMatrix;
  // Square size of cells
  int cellSize;
  // Position of the tetromino which cells are positioned relative to
  std::pair<int, int> position;
};