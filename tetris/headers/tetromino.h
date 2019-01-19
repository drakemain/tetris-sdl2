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
  Tetromino(Shape shape, int cellSize);
  Tetromino(const Tetromino& other);
  // Delete each cell and vector container
  ~Tetromino();

  // Renders the tetromino's cells
  void render();
  // Adjusts the position of each of the cells
  void shift(int gridUnitsX, int gridUnitsY);
  // Rotate the cells within the matrix CW 90 degrees
  void rotate();
  void destroy(Cell* cellToDestroy);
  void destroy();
  Tetromino* makeNewCopy();
  
  // Getters
  ShapeMatrix getShapeMatrix() const;
  int getWidth() const;
  int getHeight() const;
  std::pair<int, int> getPosition() const;
  int getBoundingBoxSize() const;
  void getCells(std::vector<Cell*>& outCells) const;

private:
  // Initializes the container for the cell pointers
  void initCells(std::array<std::array<Uint8, 4>, 4> shapeMatrix, int size);
  // Maps Uint8 to RGB struct
  SDL_Color getColor(Uint8);
  // Finds the edges of the tetromino
  int getTopEdge();
  int getBottomEdge();
  int getLeftEdge();
  int getRightEdge();

  void computeDimensions();

private:
  // Pointers to the tetromino's cells
  std::vector<Cell*> cells;
  ShapeMatrix shapeMatrix;
  // Square size of cells
  const int cellSize;
  // Position of the tetromino which cells are positioned relative to
  std::pair<int, int> position;
  // Smallest square matrix size the tetromino can fit into. Used for rotation.
  int boundingBoxSize;
  int width;
  int height;
};