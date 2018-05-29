#pragma once
#include <SDL.h>

class Cell {
public:
  Cell(SDL_Renderer* renderer);
  Cell(SDL_Renderer* renderer, Uint8 r, Uint8 g, Uint8 b);
  ~Cell();

  void setColor(SDL_Renderer* renderer, Uint8 r, Uint8 g, Uint8 b);

  void render(SDL_Renderer* renderer);

  SDL_Texture* getCell() const;

  void setPosition(int x, int y);
  void setDimensions(int w, int h);
  void shift(int gridX, int gridY);

private:
  SDL_Texture* cell;
  SDL_Rect container;
};