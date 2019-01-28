#pragma once
#include <SDL.h>
#include <array>

class Player {
public:
  Player(class Board* board);

  static unsigned int count;

  const unsigned int id = 0;

  void tick(unsigned int deltaTme);

  void handleInput(SDL_Keycode key);

  void reset();

  bool checkHasLost() const;
  
  unsigned int getScore() const;
private:
  std::array<SDL_Keycode, 4> inputSchema;
  void incrementScore(const unsigned int amount);
  bool hasLost = false;

  unsigned int score = 0;
  class Board* board = nullptr;
};