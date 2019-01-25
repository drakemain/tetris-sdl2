#pragma once
#include "tetris/headers/Base.h"
#include <vector>
#include <SDL.h>

class Tetris : Base {
public:
  Tetris(){};
  Tetris(bool devMode): devMode(devMode){};
  // SDL Initialization
  bool init(uint players);
  // Contains game loop
  void run();
  // Cleanup assets
  void cleanup();

private:
  void render();
  void inputHandler();
  void keyboardHandler(SDL_Keycode key);
  void tick(uint deltaTime);
  void togglePause();
  void reset();

private:
  std::vector<class Board*> boards;
  std::vector<class Player*> players;
  class Input* input;
  class Scoreboard* scoreboard;
  bool devMode = false;
  bool isRunning = true;
  bool isPaused = false;
  bool hasLost = false;

  const int WINDOW_WIDTH = 1280;
  const int WINDOW_HEIGHT = 1024;
};