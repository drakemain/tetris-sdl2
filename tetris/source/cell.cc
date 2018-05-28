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

void Cell::setPositionX(int x) {
  this->cellContainer.x = x;
}

void Cell::setPositionY(int y) {
  this->cellContainer.y = y;
}

void Cell::incrementX(bool negative = false, int gridUnits = 1) {
  if (negative) {
    this->cellContainer.x -= gridUnits * 25;
  } else {
    this->cellContainer.x += gridUnits * 25;
  }
}

void Cell::incrementY(bool negative = false, int gridUnits = 1) {
  if (negative) {
    this->cellContainer.y -= gridUnits * 25;
  } else {
    this->cellContainer.y += gridUnits * 25;
  }
} 