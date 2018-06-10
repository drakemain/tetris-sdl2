#include "tetris/headers/board.h"
#include <iostream>

Board::Board(int heightBound) {
  this->board.x = 0;
  this->board.y = 0;

  this->gridUnitPixels = heightBound / this->GRID_HEIGHT;

  this->board.w = this->gridUnitPixels * this->GRID_WIDTH;
  this->board.h = this->gridUnitPixels * this->GRID_HEIGHT;

  this->grid.resize(this->GRID_HEIGHT);
  for (int i = 0; i < this->GRID_HEIGHT; ++i) {
    this->grid[i].resize(this->GRID_WIDTH);
  }
}

Board::~Board() {
  for (Tetromino* tetromino : this->placedTetrominos) {
    delete tetromino;
  }
}

void Board::placeTetromino(Tetromino* tetromino) {
  this->placedTetrominos.push_back(tetromino);

  std::vector<Cell*> tetrominoCells;
  tetromino->getCells(tetrominoCells);

  for (Cell* cell : tetrominoCells) {
    std::pair<int, int> position = cell->getBoardPosition();
    this->grid[position.second][position.first] = cell;
  }
}

void Board::render(SDL_Renderer* renderer) {
  SDL_RenderSetViewport(renderer, &this->board);
  SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
  SDL_SetRenderDrawColor(renderer, 255, 255, 255, 100);
  SDL_RenderFillRect(renderer, NULL);

  SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_NONE);
  for (Tetromino* placedTetromino : this->placedTetrominos) {
    placedTetromino->render(renderer);
  }
}

int Board::getWidth() const {
  return this->board.w;
}

int Board::getHeight() const {
  return this->board.h;
}

int Board::getGridUnitPixels() const {
  return this->gridUnitPixels;
}