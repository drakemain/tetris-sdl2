#include "tetris/headers/player.h"
#include "tetris/headers/board.h"
#include <array>

std::array<std::array<SDL_Keycode, 4>, 4> inputSchemas = {
  std::array<SDL_Keycode, 4>{SDLK_w, SDLK_a, SDLK_s, SDLK_d},
  std::array<SDL_Keycode, 4>{SDLK_t, SDLK_f, SDLK_g, SDLK_h},
  std::array<SDL_Keycode, 4>{SDLK_i, SDLK_j, SDLK_k, SDLK_l},
  std::array<SDL_Keycode, 4>{SDLK_UP, SDLK_LEFT, SDLK_DOWN, SDLK_RIGHT}
};

unsigned int Player::count = 0;

Player::Player(Board* board)
: id(Player::count), board(board)
{
  this->inputSchema = inputSchemas[Player::count];
  ++Player::count;
}

void Player::incrementScore(const unsigned int amount) {
  this->score += amount;
}

void Player::tick(uint deltaTime) {
  this->board->tick(deltaTime);
  this->hasLost = this->board->checkHasLost();
  this->score += this->board->getDeltaPoints();
}

void Player::handleInput(SDL_Keycode key) {
  if (key == this->inputSchema[0]) {
    this->board->rotateActiveTetromino();
  } else if (key == this->inputSchema[1]) {
    this->board->shiftActiveTetromino(-1, 0);
  } else if (key == this->inputSchema[2]) {
    this->board->shiftActiveTetromino(0, 1);
  } else if (key == this->inputSchema[3]) {
    this->board->shiftActiveTetromino(1, 0);
  }
}

void Player::reset() {
  this->score = 0;
  this->hasLost = false;
}

bool Player::checkHasLost() const {
  return this->hasLost;
}

uint Player::getScore() const {
  return this->score;
}