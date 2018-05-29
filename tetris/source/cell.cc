#include "tetris/headers/cell.h"
#include <iostream>

Cell::Cell(SDL_Renderer* renderer) {
  SDL_CreateRGBSurface(0, 5, 5, 32, 0, 0, 0, 0);

  SDL_Surface* surface = SDL_CreateRGBSurface(0, 5, 5, 32, 0, 0, 0, 0);

  this->cell = SDL_CreateTextureFromSurface(renderer, surface);
  SDL_FreeSurface(surface);

  this->cellContainer.x = 25;
  this->cellContainer.y = 25;
  this->cellContainer.w = 25;
  this->cellContainer.h = 25;
}

Cell::~Cell() {
  SDL_DestroyTexture(this->cell);
  std::cout << "Cell deleted." << std::endl;
}

void Cell::setColor(SDL_Renderer* renderer, Uint8 r, Uint8 g, Uint8 b) {
  SDL_Surface* surface = SDL_CreateRGBSurface(0, 5, 5, 32, 0, 0, 0, 0);
  SDL_FillRect(surface, NULL, SDL_MapRGB(surface->format, r, g, b));
  
  SDL_DestroyTexture(this->cell);
  this->cell = SDL_CreateTextureFromSurface(renderer, surface);
  SDL_FreeSurface(surface);
}

void Cell::render(SDL_Renderer* renderer) {
  SDL_RenderCopy(renderer, this->cell, NULL, &this->cellContainer);
}

SDL_Texture* Cell::getCell() const {
  return this->cell;
}

void Cell::setPosition(int x, int y) {
  this->cellContainer.x = x;
  this->cellContainer.y = y;
}

void Cell::shift(int gridX, int gridY) {
  this->cellContainer.x += gridX * 25;
  this->cellContainer.y += gridY * 25;
}