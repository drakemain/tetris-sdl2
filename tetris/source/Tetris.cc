#include "tetris/headers/Tetris.h"
#include "tetris/headers/tetromino.h"
#include "tetris/headers/board.h"
#include "tetris/headers/input.h"
#include "tetris/headers/player.h"
#include "tetris/headers/scoreboard.h"
#include <SDL_ttf.h>
#include <iostream>

bool Tetris::init(uint players = 1) {
  std::cout << "INIT" << std::endl;
  bool success = true;
  srand(time(0));

  if (this->devMode) { std::cout << "Dev mode is enabled." << std::endl; }

  if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
    success = false;
    return success;
  }

  if (TTF_Init() != 0) {
    return false;
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

  for (uint i = 0; i < players; ++i) {
    Board* board;

    if (this->boards.size() == 0) {
      board = new Board(this->WINDOW_HEIGHT, 0);
    } else {
      board = new Board(this->WINDOW_HEIGHT, this->boards[i-1]->getWidth() * i);
    }

    Uint8 colorValue = (Uint8)(255 - (25 * i));

    board->setBackgroundColor({colorValue, colorValue, colorValue, 100});
    
    Player* player = new Player(board);

    this->boards.push_back(board);
    this->players.push_back(player);
  }

  this->input = new Input();
  this->scoreboard = new Scoreboard("tetris/RobotoMono-Medium.ttf");
  this->scoreboard->init(this->players);
  this->scoreboard->setWidth(this->WINDOW_WIDTH - this->boards[0]->getWidth() * this->boards.size());
  
  this->scoreboard->setHeight(100);
  
  this->scoreboard->setPosition(this->boards[0]->getWidth() * this->boards.size(), 0);
  
  std::cout << "Init successful." << std::endl;
  return success;
}

void Tetris::run() {
  std::cout << "RUN" << std::endl;
  const int frameCap = 60;
  const float minFrameTime = 1000.f / frameCap;

  uint runTime = 0;
  uint deltaTime = 0;
  uint timeSinceLastFrame = 0;
  uint lastTickTime = 0;

  for (Board* board : this->boards) {
    board->generateNewActiveTetromino();
  }

  while(this->isRunning) {
    runTime = SDL_GetTicks();
    deltaTime = runTime - lastTickTime;
    lastTickTime = runTime;

    this->inputHandler();

    this->tick(deltaTime);

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

  delete this->input;

  for (Player* player : this->players) {
    delete player;
  }

  for (Board* board : this->boards) {
    delete board;
  }

  this->clearRenderer();
  this->destroyWindow();

  SDL_Quit();
  TTF_Quit();
}

void Tetris::render() {
  SDL_SetRenderDrawColor(this->getRenderer(), 0, 127, 255, 0);
  SDL_RenderClear(this->getRenderer());

  for (Board* board : this->boards) {
    board->render(this->getRenderer());
  }

  this->scoreboard->render();

  SDL_RenderPresent(this->getRenderer());
}

void Tetris::inputHandler() {
  if (this->input->poll()) {
    switch(this->input->getType()) {
      case SDL_QUIT:
      this->isRunning = false; break;

      case SDL_KEYDOWN:
      this->keyboardHandler(this->input->getKeyCode()); break;
    }
  }
}

void Tetris::keyboardHandler(SDL_Keycode key) {
  if (key == SDLK_r) {
    this->reset();
  }
  
  if (!this->hasLost) {
    if (key == SDLK_p) {
      this->togglePause();
    }

    if (this->isPaused) { return; }
    
    for (Player* player : this->players) {
      player->handleInput(key);
    }
  }


  // if (this->devMode) {
  //   switch(key) {
  //     case SDLK_SPACE:
  //     this->board->createGhost();
  //     break;

  //     case SDLK_SLASH:
  //     this->board->generateNewActiveTetromino();
  //     break;

  //     case SDLK_BACKSLASH:
  //     this->board->printGrid();
  //     break;

  //     case SDLK_DELETE:
  //     this->board->destroyActiveTetromino();
  //     break;

  //     case SDLK_1:
  //     this->board->generateNewActiveTetromino(Shape::I);
  //     break;

  //     case SDLK_2:
  //     this->board->generateNewActiveTetromino(Shape::J);
  //     break;

  //     case SDLK_3:
  //     this->board->generateNewActiveTetromino(Shape::L);
  //     break;

  //     case SDLK_4:
  //     this->board->generateNewActiveTetromino(Shape::O);
  //     break;

  //     case SDLK_5:
  //     this->board->generateNewActiveTetromino(Shape::S);
  //     break;

  //     case SDLK_6:
  //     this->board->generateNewActiveTetromino(Shape::T);
  //     break;

  //     case SDLK_7:
  //     this->board->generateNewActiveTetromino(Shape::Z);
  //     break;
  //   }
  // }
}

void Tetris::tick(uint deltaTime) {
  if (!this->isPaused) {
    for (Player* player : this->players) {
      player->tick(deltaTime);

      if (player->checkHasLost()) {
        this->hasLost = true;
        this->isPaused = true;
      }
    }

    this->scoreboard->update(this->players);
  }
}

void Tetris::togglePause() {
  this->isPaused = !this->isPaused;
}

void Tetris::reset() {
  for (Player* player : this->players) {
    player->reset();
  }

  for (Board* board : this->boards) {
    board->reset();
  }

  this->hasLost = false;
  this->isPaused = false;
}