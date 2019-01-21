#pragma once
#include <SDL.h>

class Player {
public:
  Player(class Board* board);

  static unsigned int count;

  const unsigned int id = 0;

  void tick(unsigned int deltaTme);

  void handleInput(SDL_Keycode key);
  
  unsigned int getScore() const;
private:
  void incrementScore(const unsigned int amount);

  unsigned int score = 0;
  class Board* board;
};