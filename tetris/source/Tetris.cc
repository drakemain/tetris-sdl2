#include "tetris/headers/Tetris.h"
#include <SDL_image.h>
#include <iostream>
#include <cmath>

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

  this->board = new Board(this->WINDOW_HEIGHT);
  std::cout << "Init successful." << std::endl;
  return success;
}

void Tetris::run() {
  const int frameCap = 60;
  const float frameTime = 1000 / frameCap;

  float runTime = 0;
  float deltaTime = 0;
  float lastFrameTime = 0;

  this->board->generateNewActiveTetromino(this->renderer);
  std::cout << "RUN" << std::endl;
  bool isRunning = true;
  SDL_Event event;

  while(isRunning) {
    runTime = SDL_GetTicks();
    deltaTime += runTime - lastFrameTime;
    lastFrameTime = runTime;

    if (SDL_PollEvent(&event) > 0) {
      if (event.type == SDL_QUIT) {
        isRunning = false;
      } else if (event.type == SDL_KEYDOWN) {
        SDL_Keycode key = event.key.keysym.sym;
        this->keyboardHandler(key);
      }
    }

    if (deltaTime >= frameTime) {
      std::cout << pow(deltaTime/1000, -1.f) << std::endl;
      deltaTime = 0;
      this->render();
    }
  }
}

void Tetris::cleanup() {
  std::cout << "CLEANUP" << std::endl;

  delete this->board;

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

  SDL_RenderPresent(this->renderer);
}

void Tetris::keyboardHandler(SDL_Keycode key) {
  std::pair<int, int> bounds;
  bounds.first = this->board->getWidth();
  bounds.second = this->board->getHeight();

  switch(key) {
    case SDLK_RIGHT:
    this->board->shiftActiveTetromino(1, 0);
    break;

    case SDLK_LEFT:
    this->board->shiftActiveTetromino(-1, 0);
    break;

    case SDLK_UP:
    this->board->shiftActiveTetromino(0, -1);
    break;

    case SDLK_DOWN:
    this->board->shiftActiveTetromino(0, 1);
    break;

    case SDLK_SPACE:
    this->board->rotateActiveTetromino();
    break;

    case SDLK_SLASH:
    this->board->generateNewActiveTetromino(this->renderer);
    break;
  }
}