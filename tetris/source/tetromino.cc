#include "tetris/headers/tetromino.h"
#include <iostream>

typedef std::array<std::array<Uint8, 4>, 4> ShapeMatrix;


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

Tetromino::Tetromino(SDL_Renderer* renderer, Shape shape) {
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
  
  this->initCells(renderer, shapeMatrix);
}

Tetromino::~Tetromino() {
  for (std::vector<Cell*>* row : this->cellContainer) {
    for (std::size_t j = 0; j < row->size(); ++j) {
      delete row->operator[](j);
    }
    delete row;
  }
}

void Tetromino::render(SDL_Renderer* renderer) {
  for (std::vector<Cell*>* row : this->cellContainer) {
    for (std::size_t j = 0; j < row->size(); ++j) {
      Cell* cell = row->operator[](j);
      
      if (cell != NULL) {
        cell->render(renderer);
      }
    }
  }
}

void Tetromino::shift(int gridUnitsX = 0, int gridUnitsY = 0) {
  for (std::vector<Cell*>* row : this->cellContainer) {
    for (std::size_t j = 0; j < row->size(); ++j) {
      Cell* cell = row->operator[](j);
      
      if (cell != NULL) {
        cell->shift(gridUnitsX, gridUnitsY);
      }
    }
  }
}

void Tetromino::initCells(SDL_Renderer* renderer, ShapeMatrix shape) {
  SDL_Color color;
  
  for (int i = 0; i < 4; ++i) {
    std::vector<Cell*>* row = new std::vector<Cell*>;
    this->cellContainer.push_back(row);

    for (int j = 0; j < 4; ++j) {
      if (shape[j][i] == 0) {
        this->cellContainer[i]->push_back(NULL);
      } else {
        color = this->getColor(shape[j][i]);
        this->cellContainer[i]->push_back(new Cell(renderer, color.r, color.g, color.b));
        this->cellContainer[i]->operator[](j)->shift(i, j);
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