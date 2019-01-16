#include "tetris/headers/cell.h"
#include "tetris/headers/tetromino.h"
#include <iostream>

Cell::Cell(int size, Tetromino* owner): owner(owner) {
  SDL_Surface* surface = SDL_CreateRGBSurface(0, 5, 5, 32, 0, 0, 0, 0);

  this->cell = SDL_CreateTextureFromSurface(this->getRenderer(), surface);
  SDL_FreeSurface(surface);

  this->container.x = 0;
  this->container.y = 0;
  this->container.w = size;
  this->container.h = size;
}

Cell::Cell(Uint8 r, Uint8 g, Uint8 b, int size, Tetromino* owner): owner(owner) {
  this->setColor(r, g, b);

  this->container.x = 0;
  this->container.y = 0;
  this->container.w = size;
  this->container.h = size;
}

Cell::~Cell() {
  SDL_DestroyTexture(this->cell);
}

void Cell::setColor(Uint8 r, Uint8 g, Uint8 b) {
  SDL_Surface* surface = SDL_CreateRGBSurface(0, 5, 5, 32, 0, 0, 0, 0);
  SDL_FillRect(surface, NULL, SDL_MapRGB(surface->format, r, g, b));
  
  SDL_DestroyTexture(this->cell);
  this->cell = SDL_CreateTextureFromSurface(this->getRenderer(), surface);
  SDL_FreeSurface(surface);
}

void Cell::render() {
  SDL_RenderCopy(this->getRenderer(), this->cell, NULL, &this->container);
}

void Cell::shift(int gridX, int gridY) {
  this->container.x += gridX * this->container.w;
  this->container.y += gridY * this->container.h;
}

void Cell::setPosition(int x, int y) {
  this->container.x = x * this->container.w;
  this->container.y = y * this->container.h;
}

std::pair<int, int> Cell::getPixelPosition() const {
  std::pair<int, int> position;

  position.first = this->container.x;
  position.second = this->container.y;
  
  return position;
}

std::pair<int, int> Cell::getBoardPosition() const {
  std::pair<int, int> position;
  std::pair<int, int> pixelPosition = this->getPixelPosition();

  position.first = pixelPosition.first / this->getSize();
  position.second = pixelPosition.second / this->getSize();

  return position;
}

int Cell::getSize() const {
  // cell should always be square
  return this->container.w;
}

Tetromino* Cell::getOwner() {
  return this->owner;
}

void Cell::destroy() {
  delete this;
}