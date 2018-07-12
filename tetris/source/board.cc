#include "tetris/headers/board.h"
#include <iostream>

Board::Board(int heightBound) {
  this->board.x = 0;
  this->board.y = 0;

  this->gridUnitPixels = heightBound / this->GRID_HEIGHT;

  this->board.w = this->gridUnitPixels * this->GRID_WIDTH;
  this->board.h = this->gridUnitPixels * this->GRID_HEIGHT;

  this->grid.resize(this->GRID_HEIGHT + this->SPAWN_ROWS);
  for (int i = 0; i < this->GRID_HEIGHT + this->SPAWN_ROWS; ++i) {
    this->grid[i].resize(this->GRID_WIDTH);
  }

  this->printGrid();

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

  this->activeTetromino->render();

  SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_NONE);
  for (Tetromino* placedTetromino : this->placedTetrominos) {
    placedTetromino->render();
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

void Board::generateNewActiveTetromino() {
  this->placeActiveTetromino();
  this->activeTetromino = this->spawnRandomTetromino();

  const int boardWidth = this->getWidth();
  const int tetrominoHeight = this->activeTetromino->getHeight();
  const int gridUnitPixels = this->getGridUnitPixels();
  const int xOffset = ((boardWidth / 2) / gridUnitPixels) - 2;

  
  this->activeTetromino->shift(xOffset, -tetrominoHeight);
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
    this->timeSinceLastDrop -= dropRate;
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

  const int boardFloor = this->GRID_HEIGHT - 1;
  const int boardCeiling = -1 * this->SPAWN_ROWS;
  const int boardLeft = 0;
  const int boardRight = this->GRID_WIDTH - 1;

  if (projectedY > boardFloor || projectedY < boardCeiling) {
    return false;
  }

  if (projectedX > boardRight || projectedX < boardLeft) {
    return false;
  }
  
  return true;
}

bool Board::collisionCheck(Cell* cell, int xDelta, int yDelta) {
  std::pair<int, int> cellPosition = cell->getBoardPosition();
  int projectedX = cellPosition.first + xDelta;
  int projectedY = cellPosition.second + yDelta + this->SPAWN_ROWS;

  if (this->grid[projectedY][projectedX] == NULL) {
    return false;
  }

  return true;
}

Tetromino* Board::spawnRandomTetromino() {
  Shape shape = (Shape)(rand() % 7);
  return new Tetromino(shape, gridUnitPixels);
}

void Board::placeActiveTetromino() {
  if (this->activeTetromino == NULL) { return; }

  this->placedTetrominos.push_back(this->activeTetromino);

  std::vector<Cell*> tetrominoCells;
  this->activeTetromino->getCells(tetrominoCells);

  for (Cell* cell : tetrominoCells) {
    std::pair<int, int> position = cell->getBoardPosition();
    this->grid[position.second + this->SPAWN_ROWS][position.first] = cell;
  }

  this->activeTetromino = NULL;

  this->printGrid();
}

void Board::printGrid() {
  int rowCounter = 0;

  for (int colCounter = 0; colCounter < (int)this->grid[0].size(); ++colCounter) {
    std::cout << colCounter + 1 << " ";
  }

  std::cout << std::endl;

  for (int i = 0; i < (int)this->grid[0].size(); ++i) {
    std::cout << "--";
  }

  std::cout << std::endl;

  for (std::vector<Cell*> row : this->grid) {
    for (Cell* cell : row) {
      if (cell == nullptr) {
        std::cout << "O";
      } else {
        std::cout << "X";
      }

      std::cout << " ";
    }

    std::cout << "|" << ++rowCounter << std::endl;
  }
}