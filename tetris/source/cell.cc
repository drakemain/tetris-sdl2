#include "tetris/headers/cell.h"
#include <iostream>

Cell::Cell(SDL_Renderer* renderer, int size) {
  SDL_Surface* surface = SDL_CreateRGBSurface(0, 5, 5, 32, 0, 0, 0, 0);

  this->cell = SDL_CreateTextureFromSurface(renderer, surface);
  SDL_FreeSurface(surface);

  this->container.x = 0;
  this->container.y = 0;
  this->container.w = size;
  this->container.h = size;
}

Cell::Cell(SDL_Renderer* renderer, Uint8 r, Uint8 g, Uint8 b, int size) {
  this->setColor(renderer, r, g, b);

  this->container.x = 0;
  this->container.y = 0;
  this->container.w = size;
  this->container.h = size;
}

Cell::~Cell() {
  SDL_DestroyTexture(this->cell);
}

void Cell::setColor(SDL_Renderer* renderer, Uint8 r, Uint8 g, Uint8 b) {
  SDL_Surface* surface = SDL_CreateRGBSurface(0, 5, 5, 32, 0, 0, 0, 0);
  SDL_FillRect(surface, NULL, SDL_MapRGB(surface->format, r, g, b));
  
  SDL_DestroyTexture(this->cell);
  this->cell = SDL_CreateTextureFromSurface(renderer, surface);
  SDL_FreeSurface(surface);
}

void Cell::render(SDL_Renderer* renderer) {
  SDL_RenderCopy(renderer, this->cell, NULL, &this->container);
}

void Cell::shift(int gridX, int gridY) {
  this->container.x += gridX * this->container.w;
  this->container.y += gridY * this->container.h;
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

void Cell::setPosition(int x, int y) {
  this->container.x = x;
  this->container.y = y;
}