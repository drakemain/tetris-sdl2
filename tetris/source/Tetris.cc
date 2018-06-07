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

  this->window = SDL_CreateWindow("Tetris", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, this->WIDTH, this->HEIGHT, SDL_WINDOW_ALLOW_HIGHDPI);

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

  this->gameBoard.x = 0;
  this->gameBoard.y = 0;
  this->gameBoard.w = this->WIDTH;
  this->gameBoard.h = this->HEIGHT;

  std::cout << "Init successful." << std::endl;
  return success;
}

void Tetris::run() {
  Tetromino tetromino(this->renderer, Shape::S, this->gridUnitSize);
  std::cout << "RUN" << std::endl;
  bool isRunning = true;
  SDL_Event event;

  while(isRunning) {
    if (SDL_PollEvent(&event) > 0) {
      if (event.type == SDL_QUIT) {
        isRunning = false;
      } else if (event.type == SDL_KEYDOWN) {
        SDL_Keycode key = event.key.keysym.sym;
        std::pair<int, int> bounds;
        bounds.first = gameBoard.w;
        bounds.second = gameBoard.h;
        switch(key) {
          case SDLK_RIGHT:
          tetromino.shift(1, 0, bounds);
          break;

          case SDLK_LEFT:
          tetromino.shift(-1, 0, bounds);
          break;

          case SDLK_UP:
          tetromino.shift(0, -1, bounds);
          break;

          case SDLK_DOWN:
          tetromino.shift(0, 1, bounds);
          break;

          case SDLK_SPACE:
          tetromino.rotate(this->renderer);
          break;
        }
      }
    }
    this->render(tetromino);
  }
}

void Tetris::cleanup() {
  std::cout << "CLEANUP" << std::endl;

  SDL_RenderClear(this->renderer);
  SDL_DestroyWindow(this->window);

  SDL_Quit();
}

SDL_Renderer* Tetris::getRenderer() const {
  return this->renderer;
}

void Tetris::render(Tetromino& tetromino) {
  SDL_RenderSetViewport(this->getRenderer(), &this->gameBoard);

  SDL_SetRenderDrawColor(this->renderer, 0, 127, 255, 0);
  SDL_RenderClear(this->renderer);
  SDL_SetRenderDrawColor(this->renderer, 255, 127, 255, 0);
  tetromino.render(this->renderer);
  SDL_RenderPresent(this->renderer);
}