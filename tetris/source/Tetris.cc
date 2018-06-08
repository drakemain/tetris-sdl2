#include "tetris/headers/Tetris.h"
#include <SDL_image.h>
#include <iostream>

bool Tetris::init() {
  std::cout << "INIT" << std::endl;
  bool success = true;

  if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
    success = false;
    return success;
  }

  this->window = SDL_CreateWindow("Tetris", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, this->WINDOW_WIDTH, this->WINDOW_HEIGHT, SDL_WINDOW_ALLOW_HIGHDPI);

  if (this->window == NULL) {
    std::cerr << "Failed to create window: " << SDL_GetError() << std::endl;
    success = false;
    return success;
  }

  this->renderer = SDL_CreateRenderer(this->window, -1, SDL_RENDERER_ACCELERATED);

  if (this->renderer == NULL) {
    std::cerr << "Failed to init renderer: " << SDL_GetError() << std::endl;
    success = false;
    return success;
  }

  this->initGameBoard();

  std::cout << this->gameBoard.w << " " << this->gameBoard.h << " " << this->gridUnitSize << std::endl;

  std::cout << "Init successful." << std::endl;
  return success;
}

void Tetris::run() {
  this->generateNewActiveTetromino();
  std::cout << "RUN" << std::endl;
  bool isRunning = true;
  SDL_Event event;

  while(isRunning) {
    if (SDL_PollEvent(&event) > 0) {
      if (event.type == SDL_QUIT) {
        isRunning = false;
      } else if (event.type == SDL_KEYDOWN) {
        SDL_Keycode key = event.key.keysym.sym;
        this->keyboardHandler(key);
      }
    }
    this->render();
  }
}

void Tetris::cleanup() {
  std::cout << "CLEANUP" << std::endl;

  for (Tetromino* tetromino : this->placedTetrominos) {
    delete tetromino;
  }

  delete activeTetromino;

  SDL_RenderClear(this->renderer);
  SDL_DestroyWindow(this->window);

  SDL_Quit();
}

SDL_Renderer* Tetris::getRenderer() const {
  return this->renderer;
}

void Tetris::render() {
  SDL_RenderSetViewport(this->getRenderer(), &this->gameBoard);

  SDL_SetRenderDrawColor(this->renderer, 0, 127, 255, 0);
  SDL_RenderClear(this->renderer);
  SDL_SetRenderDrawColor(this->renderer, 255, 127, 255, 0);
  for (Tetromino* tetromino : this->placedTetrominos) {
    tetromino->render(this->renderer);
  }

  if (this->activeTetromino) {
    this->activeTetromino->render(this->renderer);
  }

  SDL_RenderPresent(this->renderer);
}

void Tetris::keyboardHandler(SDL_Keycode key) {
  std::pair<int, int> bounds;
  bounds.first = this->gameBoard.w;
  bounds.second = this->gameBoard.h;
  switch(key) {
    case SDLK_RIGHT:
    this->activeTetromino->shift(1, 0, bounds);
    break;

    case SDLK_LEFT:
    this->activeTetromino->shift(-1, 0, bounds);
    break;

    case SDLK_UP:
    this->activeTetromino->shift(0, -1, bounds);
    break;

    case SDLK_DOWN:
    this->activeTetromino->shift(0, 1, bounds);
    break;

    case SDLK_SPACE:
    this->activeTetromino->rotate(this->renderer);
    break;

    case SDLK_SLASH:
    this->placeActiveTetromino();
    this->generateNewActiveTetromino();
    break;
  }
}

void Tetris::placeActiveTetromino() {
  this->placedTetrominos.push_back(this->activeTetromino);
  this->activeTetromino = NULL;
}

void Tetris::generateNewActiveTetromino() {
  Shape shape = (Shape)(rand() % 7);
  int xOffset = ((this->gameBoard.w / 2) / this->gridUnitSize) - 2;
  std::pair<int, int> bounds(this->gameBoard.w, this->gameBoard.h);

  this->activeTetromino = new Tetromino(this->renderer, shape, this->gridUnitSize);
  this->activeTetromino->shift(xOffset, 0, bounds);
}

void Tetris::initGameBoard() {
  this->gameBoard.x = 0;
  this->gameBoard.y = 0;

  int gridSize = this->WINDOW_HEIGHT / this->BOARD_GRID_HEIGHT;
  this->gridUnitSize = gridSize;

  this->gameBoard.w = gridSize * this->BOARD_GRID_WIDTH;
  this->gameBoard.h = gridSize * this->BOARD_GRID_HEIGHT;
}