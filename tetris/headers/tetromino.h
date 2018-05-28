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
  // Tetromino(Shape shape);
  Tetromino(SDL_Renderer* renderer);
  ~Tetromino();

  void render(SDL_Renderer* renderer);
  void shift(int gridUnitsX, int gridUnitsY);

private:
  void initMatrix(SDL_Renderer* renderer);

private:
  std::vector<std::vector<Cell*>*> matrix;
};