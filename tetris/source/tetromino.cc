#include "tetris/headers/tetromino.h"
#include <iostream>

typedef std::array<std::array<Uint8, 4>, 4> ShapeMatrix;

ShapeMatrix I =
{
  std::array<Uint8, 4>{0,1,0,0},
  std::array<Uint8, 4>{0,1,0,0},
  std::array<Uint8, 4>{0,1,0,0},
  std::array<Uint8, 4>{0,1,0,0}
};

ShapeMatrix J = {
  std::array<Uint8, 4>{0,0,1,0},
  std::array<Uint8, 4>{0,0,1,0},
  std::array<Uint8, 4>{0,1,1,0},
  std::array<Uint8, 4>{0,0,0,0}
};

ShapeMatrix L = {
  std::array<Uint8, 4>{0,1,0,0},
  std::array<Uint8, 4>{0,1,0,0},
  std::array<Uint8, 4>{0,1,1,0},
  std::array<Uint8, 4>{0,0,0,0}
};

ShapeMatrix O = {
  std::array<Uint8, 4>{0,1,1,0},
  std::array<Uint8, 4>{0,1,1,0},
  std::array<Uint8, 4>{0,0,0,0},
  std::array<Uint8, 4>{0,0,0,0}
};

ShapeMatrix S = {
  std::array<Uint8, 4>{0,1,1,0},
  std::array<Uint8, 4>{1,1,0,0},
  std::array<Uint8, 4>{0,0,0,0},
  std::array<Uint8, 4>{0,0,0,0}
};

ShapeMatrix T = {
  std::array<Uint8, 4>{1,1,1,0},
  std::array<Uint8, 4>{0,1,0,0},
  std::array<Uint8, 4>{0,0,0,0},
  std::array<Uint8, 4>{0,0,0,0}
};

ShapeMatrix Z = {
  std::array<Uint8, 4>{1,1,0,0},
  std::array<Uint8, 4>{0,1,1,0},
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
  for (int i = 0; i < 4; ++i) {
    std::vector<Cell*>* row = new std::vector<Cell*>;
    this->cellContainer.push_back(row);

    for (int j = 0; j < 4; ++j) {
      if (shape[j][i] == 0) {
        this->cellContainer[i]->push_back(NULL);
      } else {
        this->cellContainer[i]->push_back(new Cell(renderer, i * 32, j * 32, 127));
        this->cellContainer[i]->operator[](j)->shift(i, j);
      }
    }
  }

  // for (std::size_t i = 0; i < 4; ++i) {
  //   std::vector<Cell*>* row = new std::vector<Cell*>;
  //   this->cellContainer.push_back(row);
  //   for (std::size_t j = 0; j < 4; ++j) {
  //     cellContainer[i]->push_back(new Cell(renderer, i * 32, j * 32, 127));
  //     cellContainer[i]->operator[](j)->shift(i, j);
  //   }
  // }
}