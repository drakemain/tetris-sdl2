#include "tetris/headers/player.h"
#include "tetris/headers/board.h"

Player::Player(Board* board)
: board(board) {}

void Player::incrementScore(const unsigned int amount) {
  this->score += amount;
}

void Player::tick(uint deltaTime) {
  this->board->tick(deltaTime);
  this->score += this->board->getDeltaPoints();
}

void Player::handleInput(SDL_Keycode key) {
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
}

uint Player::getScore() const {
  return this->score;
}