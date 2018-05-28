#include "tetris/headers/tetromino.h"
#include <iostream>

// Tetromino::Tetromino(Shape shape) {
  
// }

Tetromino::Tetromino(SDL_Renderer* renderer) {
  this->initMatrix(renderer);
}

Tetromino::~Tetromino() {
  for (std::vector<Cell*>* row : this->matrix) {
    for (std::size_t j = 0; j < row->size(); ++j) {
      delete row->operator[](j);
    }
    delete row;
  }
}

void Tetromino::initMatrix(SDL_Renderer* renderer) {
  for (std::size_t i = 0; i < 4; ++i) {
    std::vector<Cell*>* row = new std::vector<Cell*>;
    this->matrix.push_back(row);
    for (std::size_t j = 0; j < 4; ++j) {
      matrix[i]->push_back(new Cell(renderer));
    }
  }

  for (std::size_t i = 0; i < this->matrix.size(); ++i) {
    std::cout << i << std::endl;
    for (std::size_t j = 0; j < this->matrix[i]->size(); ++j) {
      std::cout << "\t" << j << std::endl;
    }
  }
}