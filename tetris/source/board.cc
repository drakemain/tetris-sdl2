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
}

Board::~Board() {
  for (Tetromino* tetromino : this->placedTetrominos) {
    delete tetromino;
  }

  delete this->activeTetromino;
  delete this->dropGhost;
}

void Board::render(SDL_Renderer* renderer) {
  SDL_RenderSetViewport(renderer, &this->board);
  SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
  SDL_SetRenderDrawColor(renderer, 255, 255, 255, 100);
  SDL_RenderFillRect(renderer, NULL);
  SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_NONE);

  if (this->activeTetromino) {
    this->activeTetromino->render();
  }

  if (this->dropGhost) {
    this->dropGhost->render();
  }

  for (Tetromino* placedTetromino : this->placedTetrominos) {
    placedTetromino->render();
  }
}

bool Board::shiftActiveTetromino(int x, int y) {
  if (this->activeTetromino == NULL) { return false; }

  if (this->isValidMove(this->activeTetromino, x, y)) {
    this->activeTetromino->shift(x, y);

    std::cout << this->dropGhost->getPosition().second << std::endl;
    
    if (x != 0) {
      this->adjustGhost(x);
    }

    return true;
  }

  return false;
}

bool Board::rotateActiveTetromino() {
  if (this->activeTetromino == NULL) { return false; }

  bool validRotation = false;

  if (this->activeTetromino->validRotate(this->GRID_WIDTH, this->GRID_HEIGHT)) {
    if (this->dropGhost) {
      this->dropGhost->rotate();
      this->adjustGhost(0);
    }

    validRotation = true;
  }

  return validRotation;
}

void Board::generateNewActiveTetromino() {
  if (this->activeTetromino) { this->destroyActiveTetromino(); }
  
  this->activeTetromino = this->spawnRandomTetromino();

  const int boardWidth = this->getWidth();
  const int tetrominoHeight = this->activeTetromino->getHeight();
  const int gridUnitPixels = this->getGridUnitPixels();
  const int xOffset = ((boardWidth / 2) / gridUnitPixels) - 2;

  this->activeTetromino->shift(xOffset, -tetrominoHeight);
  this->createGhost();
}

void Board::generateNewActiveTetromino(Shape shape) {
  if (this->activeTetromino) { this->destroyActiveTetromino(); }
  
  this->activeTetromino = new Tetromino(shape, this->getGridUnitPixels());

  const int boardWidth = this->getWidth();
  const int tetrominoHeight = this->activeTetromino->getHeight();
  const int gridUnitPixels = this->getGridUnitPixels();
  const int xOffset = ((boardWidth / 2) / gridUnitPixels) - 2;

  this->activeTetromino->shift(xOffset, -tetrominoHeight);
  this->createGhost();
}

void Board::destroyActiveTetromino() {
  if (this->activeTetromino) {
    this->activeTetromino->destroy();
    this->activeTetromino = NULL;
  }

  if (this->dropGhost) {
    this->dropGhost->destroy();
  }
}

void Board::createGhost() {
  if (this->dropGhost) {
    this->dropGhost->destroy();
  }

  if (this->activeTetromino) {
    std::vector<Cell*> cells;
    this->dropGhost = activeTetromino->makeNewCopy();
    this->dropGhost->setAlpha(96);

    this->dropGhost->getCells(cells);

    while(this->isValidMove(this->dropGhost, 0, 1)) {
      this->dropGhost->shift(0, 1);
    }
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

void Board::tick(uint deltaTime) {
  this->timeSinceLastDrop += deltaTime;
  
  if (this->timeSinceLastDrop >= this->dropRate) {
    this->timeSinceLastDrop -= dropRate;
    if (!this->shiftActiveTetromino(0, 1)) {
      this->placeActiveTetromino();
      
      std::vector<int> filledRows = this->findFilledRows();
      
      if (!filledRows.empty()) {
        for (int row : filledRows) {
          this->clearRow(row);
        }

        for (int cleared : filledRows) {
          for (int i = cleared; i >= this->SPAWN_ROWS; --i) {
            this->shiftDown(i - 1);
          }
        }
      }

      this->generateNewActiveTetromino();
    }
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

void Board::adjustGhost(int x) {
  if (!this->dropGhost) { return; }

  std::pair<int, int> currentPos = this->dropGhost->getPosition();
  std::pair<int, int> targetPos = this->activeTetromino->getPosition();

  this->dropGhost->shift(x, -(currentPos.second - targetPos.second));

  while (this->isValidMove(this->dropGhost, 0, 1)) {
    this->dropGhost->shift(0, 1);
  }
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

bool Board::boundsCheck(Tetromino& tetromino, int xDelta, int yDelta) {
  std::vector<Cell*> cells;
  tetromino.getCells(cells);
  bool result = true;
  
  for (Cell* cell : cells) {
    if (!this->boundsCheck(cell, xDelta, yDelta)) {
      result = false;
      break;
    }
  }

  return result;
}

bool Board::collisionCheck(Cell* cell, int xDelta, int yDelta) {
  std::pair<int, int> cellPosition = cell->getBoardPosition();
  int projectedX = cellPosition.first + xDelta;
  int projectedY = cellPosition.second + yDelta + this->SPAWN_ROWS;

  if (this->grid[projectedY][projectedX] == nullptr) {
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
}

std::vector<int> Board::findFilledRows() {
  int rowIndex = 0;
  std::vector<int> filledRows;

  for (std::vector<Cell*> row : this->grid) {
    if (this->isFilledRow(row)) {
      filledRows.push_back(rowIndex);
    }

    ++rowIndex;
  }

  return filledRows;
}

void Board::clearRow(const int row) {
  for (Cell* cell : this->grid[row]) {
    std::pair<int, int> pos = cell->getBoardPosition();
    cell->getOwner()->destroy(cell);
    this->grid[pos.second + this->SPAWN_ROWS][pos.first] = nullptr;
  }
}

void Board::shiftDown(const int row) {
  if (row <= this->GRID_HEIGHT + this->SPAWN_ROWS - 2) {
    if (row >= this->SPAWN_ROWS) {
      for (Cell* cell : this->grid[row]) {
        if (cell != nullptr) {
          std::pair<int, int> pos = cell->getBoardPosition();
          std::pair<int, int> newPos = pos;
          newPos.second += 1;
          this->grid[newPos.second + this->SPAWN_ROWS][newPos.first] = cell;
          cell->shift(0, 1);
          this->grid[pos.second + this->SPAWN_ROWS][pos.first] = nullptr;
        }
      }
    }
  }
}

bool Board::isFilledRow(std::vector<Cell*>& row) const {
  for (Cell* cell : row) {
    if (cell == nullptr) {
      return false;
    }
  }

  return true;
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