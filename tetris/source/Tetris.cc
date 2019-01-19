#include "tetris/headers/Tetris.h"
#include <SDL_image.h>
#include <iostream>

bool Tetris::init() {
  std::cout << "INIT" << std::endl;
  bool success = true;
  srand(time(0));

  if (this->devMode) { std::cout << "Dev mode is enabled." << std::endl; }

  if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
    success = false;
    return success;
  }

  this->setWindow(SDL_CreateWindow("Tetris", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, this->WINDOW_WIDTH, this->WINDOW_HEIGHT, SDL_WINDOW_ALLOW_HIGHDPI));

  if (this->getWindow() == NULL) {
    std::cerr << "Failed to create window: " << SDL_GetError() << std::endl;
    success = false;
    return success;
  }

  this->setRenderer(SDL_CreateRenderer(this->getWindow(), -1, SDL_RENDERER_ACCELERATED));

  if (this->getRenderer() == NULL) {
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
  const float minFrameTime = 1000.f / frameCap;

  uint runTime = 0;
  uint deltaTime = 0;
  uint timeSinceLastFrame = 0;
  uint lastTickTime = 0;

  this->board->generateNewActiveTetromino();
  std::cout << "RUN" << std::endl;
  bool isRunning = true;

  while(isRunning) {
    runTime = SDL_GetTicks();
    deltaTime = runTime - lastTickTime;
    lastTickTime = runTime;

    if (this->input.poll()) {
      switch(this->input.getType()) {
        case SDL_QUIT:
        isRunning = false; break;

        case SDL_KEYDOWN:
        this->keyboardHandler(this->input.getKeyCode()); break;
      }
    }
    
    this->board->tick(deltaTime);

    if (timeSinceLastFrame >= minFrameTime) {
      timeSinceLastFrame = 0;
      this->render();
    } else {
      timeSinceLastFrame += deltaTime;
    }
  }
}

void Tetris::cleanup() {
  std::cout << "CLEANUP" << std::endl;

  delete this->board;

  this->clearRenderer();
  this->destroyWindow();

  SDL_Quit();
}

void Tetris::render() {
  SDL_SetRenderDrawColor(this->getRenderer(), 0, 127, 255, 0);
  SDL_RenderClear(this->getRenderer());

  this->board->render(this->getRenderer());

  SDL_RenderPresent(this->getRenderer());
}

void Tetris::keyboardHandler(SDL_Keycode key) {
  switch(key) {
    case SDLK_RIGHT:
    this->board->shiftActiveTetromino(1, 0);
    break;

    case SDLK_LEFT:
    this->board->shiftActiveTetromino(-1, 0);
    break;

    case SDLK_UP:
    this->board->rotateActiveTetromino();
    break;

    case SDLK_DOWN:
    this->board->shiftActiveTetromino(0, 1);
    break;
  }

  if (this->devMode) {
    switch(key) {
      case SDLK_SPACE:
      this->board->createGhost();
      break;

      case SDLK_SLASH:
      this->board->generateNewActiveTetromino();
      break;

      case SDLK_BACKSLASH:
      this->board->printGrid();
      break;

      case SDLK_DELETE:
      this->board->destroyActiveTetromino();
      break;

      case SDLK_1:
      this->board->generateNewActiveTetromino(Shape::I);
      break;

      case SDLK_2:
      this->board->generateNewActiveTetromino(Shape::J);
      break;

      case SDLK_3:
      this->board->generateNewActiveTetromino(Shape::L);
      break;

      case SDLK_4:
      this->board->generateNewActiveTetromino(Shape::O);
      break;

      case SDLK_5:
      this->board->generateNewActiveTetromino(Shape::S);
      break;

      case SDLK_6:
      this->board->generateNewActiveTetromino(Shape::T);
      break;

      case SDLK_7:
      this->board->generateNewActiveTetromino(Shape::Z);
      break;
    }
  }
}