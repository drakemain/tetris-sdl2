#include "tetris/headers/tetromino.h"
#include "iostream"

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

Tetromino::Tetromino(Shape shape, int cellSize)
: cellSize(cellSize) {
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
  
  this->initCells(shapeMatrix, cellSize);

  this->computeDimensions();
}

Tetromino::Tetromino(const Tetromino& other)
: cellSize(other.cellSize) {
  this->position.first = other.position.first;
  this->position.second = other.position.second;
  std::vector<Cell*> cells;
  other.getCells(cells);
  
  for (Cell* cell : cells) {
    this->cells.push_back(cell->copy(this));
  }

  this->computeDimensions();
}

Tetromino::~Tetromino() {
  for (Cell* cell : this->cells) {
    delete cell;
  }
}

void Tetromino::render() {
  for (Cell* cell : this->cells) {
    cell->render();
  }
}

void Tetromino::shift(int gridUnitsX, int gridUnitsY) {
  this->position.first += gridUnitsX;
  this->position.second += gridUnitsY;

  for (Cell* cell : this->cells) {
    cell->shift(gridUnitsX, gridUnitsY);
  }
}

void Tetromino::rotate() {
  for (Cell* cell : this->cells) {
    std::pair<int, int> currentPosition = cell->getBoardPosition();
    std::pair<int, int> relativePosition;
    relativePosition.first = currentPosition.first - this->position.first;
    relativePosition.second = currentPosition.second - this->position.second;
    cell->setPosition(this->boundingBoxSize - 1 - relativePosition.second + this->position.first, relativePosition.first + this->position.second);
  }

  int tempValue = this->width;
  this->width = this->height;
  this->height = tempValue;
}

bool Tetromino::validRotate(int maxCol, int maxRow) {
  bool isValidRotation = true;
  std::vector<std::pair<int, int>> newPositions;
  newPositions.reserve(this->cells.size());
  
  for (Cell* cell : this->cells) {
    std::pair<int, int> currentPosition = cell->getBoardPosition();
    std::pair<int, int> relativePosition;
    std::pair<int, int> newPosition;
    relativePosition.first = currentPosition.first - this->position.first;
    relativePosition.second = currentPosition.second - this->position.second;
    newPosition.first = this->boundingBoxSize - 1 - relativePosition.second + this->position.first;
    newPosition.second = relativePosition.first + this->position.second;

    if (
      newPosition.second >= maxRow
      || newPosition.first >= maxCol || newPosition.first < 0
      ) { isValidRotation = false; break; }
      else { newPositions.push_back(newPosition); }
  }

  if (isValidRotation) {
    for (std::size_t i = 0; i < newPositions.size(); ++i) {
      this->cells[i]->setPosition(newPositions[i].first, newPositions[i].second);
    }

    int tempValue = this->width;
    this->width = this->height;
    this->height = tempValue;
  }
  
  return isValidRotation;
}

void Tetromino::setAlpha(Uint8 alpha) {
  for (Cell* cell : this->cells) {
    cell->setAlpha(alpha);
  }
}

void Tetromino::destroy() {
  delete this;
}

void Tetromino::destroy(Cell* cellToDestroy) {
  for (unsigned i = 0; i < this->cells.size(); ++i) {
    if (cellToDestroy == this->cells[i]) {
      this->cells.erase(this->cells.begin() + i);
      cellToDestroy->destroy();
    }
  }
}

Tetromino* Tetromino::makeNewCopy() {
  return new Tetromino(*this);
}

int Tetromino::getWidth() const {
  return this->width;
}

int Tetromino::getHeight() const {
  return this->height;
}

std::pair<int, int> Tetromino::getPosition() const {
  return this->position;
}

int Tetromino::getBoundingBoxSize() const {
  return this->boundingBoxSize;
}

void Tetromino::getCells(std::vector<Cell*>& outCells) const {
  for (Cell* cell : this->cells) {
    outCells.push_back(cell);
  }
}

void Tetromino::initCells(ShapeMatrix shape, int size) {
  this->cells.clear();
  SDL_Color color;

  for (std::size_t row = 0; row < shape.size(); ++row) {
    for (std::size_t column = 0; column < shape.size(); ++column) {
      if (shape[row][column] != 0) {
        color = getColor(shape[row][column]);
        this->cells.push_back(new Cell(color.r, color.g, color.b, size, this));
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

int Tetromino::getTopEdge() {
  if (this->cells.size() == 0) { return -1; }

  int edge = this->cells[0]->getPixelPosition().second;
  
  for (Cell* cell : this->cells) {
    if (cell->getPixelPosition().second < edge) {
      edge = cell->getPixelPosition().second;
    }
  }

  return edge;
}

int Tetromino::getBottomEdge() {
  if (this->cells.size() == 0) { return -1; }
  
  int edge = 0;

  for (Cell* cell : this->cells) {
    if (cell->getPixelPosition().second > edge) {
      edge = cell->getPixelPosition().second;
    }
  }

  return edge + this->cellSize;
}

int Tetromino::getLeftEdge() {
  if (this->cells.size() == 0) { return -1; }

  int edge = this->cells[0]->getPixelPosition().first;
  
  for (Cell* cell : this->cells) {
    if (cell->getPixelPosition().first < edge) {
      edge = cell->getPixelPosition().first;
    }
  }

  return edge;
}

int Tetromino::getRightEdge() {
  if (this->cells.size() == 0) { return -1; }
  
  int edge = 0;

  for (Cell* cell : this->cells) {
    if (cell->getPixelPosition().first > edge) {
      edge = cell->getPixelPosition().first;
    }
  }

  return edge + this->cellSize;
}

void Tetromino::computeDimensions() {
  int minXCell = this->cells[0]->getBoardPosition().first;
  int maxXCell = this->cells[0]->getBoardPosition().first;
  int minYCell = this->cells[0]->getBoardPosition().second;
  int maxYCell = this->cells[0]->getBoardPosition().second;
  
  for (Cell* cell : this->cells) {
    std::pair<int, int> position = cell->getBoardPosition();

    if (position.first < minXCell) { minXCell = position.first; }
    if (position.first > maxXCell) { maxXCell = position.first; }
    if (position.second < minYCell) { minYCell = position.second; }
    if (position.second > maxYCell) { maxYCell = position.second; }
  }

  int xLength = maxXCell - minXCell + 1;
  int yLength = maxYCell - minYCell + 1;

  if (xLength > yLength) {
    this->boundingBoxSize = xLength;
  } else {
    this->boundingBoxSize = yLength;
  }

  this->width = xLength;
  this->height = yLength;
}