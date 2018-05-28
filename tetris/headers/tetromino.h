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

private:
  void initMatrix(SDL_Renderer* renderer);

private:
  std::vector<std::vector<Cell*>*> matrix;
};