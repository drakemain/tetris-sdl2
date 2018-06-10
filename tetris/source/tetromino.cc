#include "tetris/headers/tetromino.h"
#include <iostream>

const ShapeMatrix I =
{
  std::array<Uint8, 4>{0,1,0,0},
  std::array<Uint8, 4>{0,1,0,0},
  std::array<Uint8, 4>{0,1,0,0},
  std::array<Uint8, 4>{0,1,0,0}
};

const ShapeMatrix J = {
  std::array<Uint8, 4>{0,0,2,0},
  std::array<Uint8, 4>{0,0,2,0},
  std::array<Uint8, 4>{0,2,2,0},
  std::array<Uint8, 4>{0,0,0,0}
};

const ShapeMatrix L = {
  std::array<Uint8, 4>{0,3,0,0},
  std::array<Uint8, 4>{0,3,0,0},
  std::array<Uint8, 4>{0,3,3,0},
  std::array<Uint8, 4>{0,0,0,0}
};

const ShapeMatrix O = {
  std::array<Uint8, 4>{0,4,4,0},
  std::array<Uint8, 4>{0,4,4,0},
  std::array<Uint8, 4>{0,0,0,0},
  std::array<Uint8, 4>{0,0,0,0}
};

const ShapeMatrix S = {
  std::array<Uint8, 4>{0,5,5,0},
  std::array<Uint8, 4>{5,5,0,0},
  std::array<Uint8, 4>{0,0,0,0},
  std::array<Uint8, 4>{0,0,0,0}
};

const ShapeMatrix T = {
  std::array<Uint8, 4>{6,6,6,0},
  std::array<Uint8, 4>{0,6,0,0},
  std::array<Uint8, 4>{0,0,0,0},
  std::array<Uint8, 4>{0,0,0,0}
};

const ShapeMatrix Z = {
  std::array<Uint8, 4>{7,7,0,0},
  std::array<Uint8, 4>{0,7,7,0},
  std::array<Uint8, 4>{0,0,0,0},
  std::array<Uint8, 4>{0,0,0,0}
};

Tetromino::Tetromino(SDL_Renderer* renderer, Shape shape, int cellSize)
:cellSize(cellSize) {
  this->position.first = 0;
  this->position.second = 0;
  ShapeMatrix shapeMatrix;

  switch(shape) {
    case Shape::I: shapeMatrix = I; break;
    case Shape::J: shapeMatrix = J; break;
    case Shape::L: shapeMatrix = L; break;
    case Shape::O: shapeMatrix = O; break;
    case Shape::S: shapeMatrix = S; break;
    case Shape::T: shapeMatrix = T; break;
    case Shape::Z: shapeMatrix = Z; break;
  }

  this->shapeMatrix = shapeMatrix;
  
  this->initCells(renderer, this->shapeMatrix, cellSize);
}

Tetromino::~Tetromino() {
  for (Cell* cell : this->cells) {
    delete cell;
  }
}

void Tetromino::render(SDL_Renderer* renderer) {
  for (Cell* cell : this->cells) {
    cell->render(renderer);
  }
}

bool Tetromino::shift(int gridUnitsX, int gridUnitsY, std::pair<int, int> bounds) {
  std::pair<int, int> positionDelta;
  positionDelta.first = gridUnitsX * this->cellSize;
  positionDelta.second = gridUnitsY * this->cellSize;

  if (!this->isWithinBounds(positionDelta, bounds)) {
    return false;
  }

  this->position.first += gridUnitsX;
  this->position.second += gridUnitsY;

  for (Cell* cell : this->cells) {
    cell->shift(gridUnitsX, gridUnitsY);
  }

  return true;
}

void Tetromino::rotate(SDL_Renderer* renderer) {
  std::array<std::array<Uint8, 4>, 4> newShapeMatrix;

  for (std::size_t currentRow = 0; currentRow < this->shapeMatrix.size(); ++currentRow) {
    for (std::size_t currentColumn = 0; currentColumn < this->shapeMatrix[currentRow].size(); ++currentColumn) {
      newShapeMatrix[currentColumn][this->shapeMatrix.size() - currentRow - 1] = this->shapeMatrix[currentRow][currentColumn];
    }
  }

  this->shapeMatrix = newShapeMatrix;

  this->initCells(renderer, this->shapeMatrix, this->cellSize);
}

bool Tetromino::isWithinBounds(std::pair<int, int> positionDelta, std::pair<int, int> bounds) {
  if ((this->getTopBound() + positionDelta.second) < 0) {
    std::cout << "TOP" << std::endl;
    return false;
  } else if ((this->getBottomBound() + positionDelta.second) > bounds.second) {
    std::cout << "BOTTOM" << std::endl;
    return false;
  } else if ((this->getLeftBound() + positionDelta.first) < 0) {
    std::cout << "LEFT" << std::endl;
    return false;
  } else if ((this->getRightBound() + positionDelta.first) > bounds.first) {
    std::cout << "RIGHT" << std::endl;
    return false;
  }

  return true;
}

void Tetromino::getCells(std::vector<Cell*>& outCells) const {
  for (Cell* cell : this->cells) {
    outCells.push_back(cell);
  }
}

void Tetromino::initCells(SDL_Renderer* renderer, ShapeMatrix shape, int size) {
  this->cells.clear();
  SDL_Color color;

  for (std::size_t row = 0; row < shape.size(); ++row) {
    for (std::size_t column = 0; column < shape.size(); ++column) {
      if (shape[row][column] != 0) {
        color = getColor(shape[row][column]);
        this->cells.push_back(new Cell(renderer, color.r, color.g, color.b, size));
        this->cells[this->cells.size() - 1]->shift(column + this->position.first, row + this->position.second);
      }
    }
  }
}

SDL_Color Tetromino::getColor(Uint8 matrixValue) {
  SDL_Color color;

  switch(matrixValue) {
    case 1:
    color.r = 0, color.g = 0; color.b = 255; color.a = 255;
    break;

    case 2:
    color.r = 255, color.g = 0; color.b = 0; color.a = 255;
    break;

    case 3:
    color.r = 0, color.g = 255; color.b = 0; color.a = 255;
    break;

    case 4:
    color.r = 255, color.g = 255; color.b = 0; color.a = 255;
    break;

    case 5:
    color.r = 173, color.g = 216; color.b = 230; color.a = 255;
    break;

    case 6:
    color.r = 160, color.g = 32; color.b = 240; color.a = 255;
    break;

    case 7:
    color.r = 255, color.g = 192; color.b = 203; color.a = 255;
    break;
  }

  return color;
}

int Tetromino::getTopBound() {
  if (this->cells.size() == 0) { return -1; }

  int bound = this->cells[0]->getPixelPosition().second;
  
  for (Cell* cell : this->cells) {
    if (cell->getPixelPosition().second < bound) {
      bound = cell->getPixelPosition().second;
    }
  }

  return bound;
}

int Tetromino::getBottomBound() {
  if (this->cells.size() == 0) { return -1; }
  
  int bound = 0;

  for (Cell* cell : this->cells) {
    if (cell->getPixelPosition().second > bound) {
      bound = cell->getPixelPosition().second;
    }
  }

  return bound + this->cellSize;
}

int Tetromino::getLeftBound() {
  if (this->cells.size() == 0) { return -1; }

  int bound = this->cells[0]->getPixelPosition().first;
  
  for (Cell* cell : this->cells) {
    if (cell->getPixelPosition().first < bound) {
      bound = cell->getPixelPosition().first;
    }
  }

  return bound;
}

int Tetromino::getRightBound() {
  if (this->cells.size() == 0) { return -1; }
  
  int bound = 0;

  for (Cell* cell : this->cells) {
    if (cell->getPixelPosition().first > bound) {
      bound = cell->getPixelPosition().first;
    }
  }

  return bound + this->cellSize;
}