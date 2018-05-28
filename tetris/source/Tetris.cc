#include "tetris/headers/Tetris.h"
#include "tetris/headers/tetromino.h"
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

  std::cout << "Init successful." << std::endl;
  return success;
}

void Tetris::run() {
  // Tetromino tetromino(this->renderer);

  std::cout << "RUN" << std::endl;
  bool isRunning = true;
  SDL_Event event;

  while(isRunning) {
    SDL_PollEvent(&event);

    if (event.type == SDL_QUIT) {
      isRunning = false;
    }

    SDL_SetRenderDrawColor(this->renderer, 0, 127, 255, 0);
    SDL_RenderClear(this->renderer);
    SDL_SetRenderDrawColor(this->renderer, 255, 127, 255, 0);
    
    SDL_RenderPresent(this->renderer);
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