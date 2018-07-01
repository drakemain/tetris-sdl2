#include "tetris/headers/board.h"

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

  srand(time(0));
}

Board::~Board() {
  for (Tetromino* tetromino : this->placedTetrominos) {
    delete tetromino;
  }

  delete this->activeTetromino;
}

void Board::render(SDL_Renderer* renderer) {
  SDL_RenderSetViewport(renderer, &this->board);
  SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
  SDL_SetRenderDrawColor(renderer, 255, 255, 255, 100);
  SDL_RenderFillRect(renderer, NULL);

  this->activeTetromino->render(renderer);

  SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_NONE);
  for (Tetromino* placedTetromino : this->placedTetrominos) {
    placedTetromino->render(renderer);
  }
}

bool Board::shiftActiveTetromino(int x, int y) {
  if (this->activeTetromino == NULL) { return false; }

  if (this->isValidMove(this->activeTetromino, x, y)) {
    this->activeTetromino->shift(x, y);
    return true;
  }

  return false;
}

bool Board::rotateActiveTetromino() {
  if (this->activeTetromino == NULL) { return false; }

  this->activeTetromino->rotate();
  return true;
}

void Board::generateNewActiveTetromino(SDL_Renderer* renderer) {
  const int boardWidth = this->getWidth();
  const int gridUnitPixels = this->getGridUnitPixels();
  const int xOffset = ((boardWidth / 2) / gridUnitPixels) - 2;

  this->placeActiveTetromino();
  this->activeTetromino = this->spawnRandomTetromino(renderer);
  this->activeTetromino->shift(xOffset, 0);
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

void Board::tick(uint deltaTime) {
  this->timeSinceLastDrop += deltaTime;
  
  if (this->timeSinceLastDrop >= this->dropRate) {
    this->timeSinceLastDrop = 0;
    this->shiftActiveTetromino(0, 1);
  }
}

bool Board::isValidMove(Tetromino* tetromino, int xDelta, int yDelta) {
  std::vector<Cell*> cells;
  tetromino->getCells(cells);

  for (Cell* cell : cells) {
    bool isWithinBounds = this->boundsCheck(cell, xDelta, yDelta);
    
    if (!isWithinBounds) {
      return false;
    }

    bool willCollide = this->collisionCheck(cell, xDelta, yDelta);

    if (willCollide) {
      return false;
    }
  }

  return true;
}

bool Board::boundsCheck(Cell* cell, int xDelta, int yDelta) {
  std::pair<int, int> cellPostion = cell->getBoardPosition();
  int projectedX = cellPostion.first + xDelta;
  int projectedY = cellPostion.second + yDelta;

  if (projectedY > (int)this->grid.size() - 1 || projectedY < 0) {
    return false;
  }

  if (projectedX > (int)this->grid[projectedY].size() - 1 || projectedX < 0) {
    return false;
  }

  return true;
}

bool Board::collisionCheck(Cell* cell, int xDelta, int yDelta) {
  std::pair<int, int> cellPosition = cell->getBoardPosition();
  int projectedX = cellPosition.first + xDelta;
  int projectedY = cellPosition.second + yDelta;

  if (this->grid[projectedY][projectedX] == NULL) {
    return false;
  }

  return true;
}

Tetromino* Board::spawnRandomTetromino(SDL_Renderer* renderer) {
  Shape shape = (Shape)(rand() % 7);
  return new Tetromino(renderer, shape, gridUnitPixels);
}

void Board::placeActiveTetromino() {
  if (this->activeTetromino == NULL) { return; }

  this->placedTetrominos.push_back(this->activeTetromino);

  std::vector<Cell*> tetrominoCells;
  this->activeTetromino->getCells(tetrominoCells);

  for (Cell* cell : tetrominoCells) {
    std::pair<int, int> position = cell->getBoardPosition();
    this->grid[position.second][position.first] = cell;
  }

  this->activeTetromino = NULL;
}