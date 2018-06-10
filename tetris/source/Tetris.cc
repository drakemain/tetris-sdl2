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

  this->board = new Board(this->WINDOW_HEIGHT, this->renderer, 255, 255, 255, 10);

  // std::cout << this->gameBoard.w << " " << this->gameBoard.h << " " << this->gridUnitSize << std::endl;

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

  delete this->board;
  delete this->activeTetromino;

  SDL_RenderClear(this->renderer);
  SDL_DestroyWindow(this->window);

  SDL_Quit();
}

SDL_Renderer* Tetris::getRenderer() const {
  return this->renderer;
}

void Tetris::render() {
  SDL_SetRenderDrawColor(this->renderer, 0, 127, 255, 0);
  SDL_RenderClear(this->renderer);

  this->board->render(this->renderer);

  if (this->activeTetromino) {
    this->activeTetromino->render(this->renderer);
  }

  SDL_RenderPresent(this->renderer);
}

void Tetris::keyboardHandler(SDL_Keycode key) {
  std::pair<int, int> bounds;
  bounds.first = this->board->getWidth();
  bounds.second = this->board->getHeight();

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
    this->board->placeTetromino(this->activeTetromino);
    this->generateNewActiveTetromino();
    break;
  }
}

void Tetris::generateNewActiveTetromino() {
  const int boardWidth = this->board->getWidth();
  const int boardHeight = this->board->getHeight();
  const int gridUnitPixels = this->board->getGridUnitPixels();

  Shape shape = (Shape)(rand() % 7);
  int xOffset = ((boardWidth / 2) / gridUnitPixels) - 2;
  std::pair<int, int> bounds(boardWidth, boardHeight);

  this->activeTetromino = new Tetromino(this->renderer, shape, gridUnitPixels);
  this->activeTetromino->shift(xOffset, 0, bounds);
}