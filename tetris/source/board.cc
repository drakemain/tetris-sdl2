#include "tetris/headers/board.h"

Board::Board(int heightBound, SDL_Renderer* renderer, Uint8 r, Uint8 g, Uint8 b, Uint8 a) {
  this->board.x = 0;
  this->board.y = 0;

  this->gridUnitPixels = heightBound / this->GRID_HEIGHT;

  this->board.w = this->gridUnitPixels * this->GRID_WIDTH;
  this->board.h = this->gridUnitPixels * this->GRID_HEIGHT;

  SDL_Surface* surface = SDL_CreateRGBSurface(0, this->board.w, this->board.h, 32, 0, 0, 0, 0);
  SDL_FillRect(surface, NULL, SDL_MapRGBA(surface->format, r, g, b, a));
  this->background = SDL_CreateTextureFromSurface(renderer, surface);
  SDL_FreeSurface(surface);
}

Board::~Board() {
  for (Tetromino* tetromino : this->placedTetrominos) {
    delete tetromino;
  }
}

void Board::placeTetromino(Tetromino* tetromino) {
  this->placedTetrominos.push_back(tetromino);
}

void Board::render(SDL_Renderer* renderer) {
  SDL_RenderCopy(renderer, this->background, NULL, &this->board);
  SDL_RenderSetViewport(renderer, &this->board);

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