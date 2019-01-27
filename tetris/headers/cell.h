#pragma once
#include "tetris/headers/Base.h"
#include <SDL.h>

class Cell : public Base {
public:
  // Constructor for default color (black)
  Cell(int size, class Tetromino* owner);
  // Constructor for custom color
  Cell(Uint8 r, Uint8 g, Uint8 b, int size, class Tetromino* owner);
  Cell(const Cell& other, Tetromino* owner);
  // Cleanup on deletion
  ~Cell();

  // Set a new color by replacing the current texture
  void setColor(Uint8 r, Uint8 g, Uint8 b);

  // Render the cell to the render target
  void render();

  Cell* copy(Tetromino* owner);

  // Set the size of the cell
  void setDimensions(int w, int h);

  void setAlpha(Uint8 alpha);

  // Adjusts the cell position
  void shift(int gridX, int gridY);
  // Sets new position
  void setPosition(int gridx, int gridY);

  // Getters
  std::pair<int, int> getPixelPosition() const;
  std::pair<int, int> getBoardPosition() const;
  int getSize() const;
  SDL_Color getColor() const;
  class Tetromino* getOwner();

  void destroy();

private:
  // Used to control the cell's color
  SDL_Texture* cell = nullptr;
  // Determines size and location to render at
  SDL_Rect container;
  SDL_Color color;

  class Tetromino* owner = nullptr;
};