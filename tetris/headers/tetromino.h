#include "tetris/headers/cell.h"
#include <vector>

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
  Tetromino(SDL_Renderer* renderer);
  // Delete each cell and vector container
  ~Tetromino();

  // Renders the tetromino's cells
  void render(SDL_Renderer* renderer);
  // Adjusts the position of each of the cells
  void shift(int gridUnitsX, int gridUnitsY);

private:
  // Initializes the container for the cell pointers
  void initMatrix(SDL_Renderer* renderer);

private:
  // Pointers to the tetromino's cells
  std::vector<std::vector<Cell*>*> matrix;
};