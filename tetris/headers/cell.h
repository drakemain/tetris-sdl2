#pragma once
#include <SDL.h>

class Cell {
public:
  // Constructor for default color (black)
  Cell(SDL_Renderer* renderer, int size);
  // Constructor for custom color
  Cell(SDL_Renderer* renderer, Uint8 r, Uint8 g, Uint8 b, int size);
  // Cleanup on deletion
  ~Cell();

  // Set a new color by replacing the current texture
  void setColor(SDL_Renderer* renderer, Uint8 r, Uint8 g, Uint8 b);

  // Render the cell to the render target
  void render(SDL_Renderer* renderer);

  // Set the size of the cell
  void setDimensions(int w, int h);

  // Adjusts the cell position
  void shift(int gridX, int gridY);
  // Sets new position
  void setPosition(int gridx, int gridY);

  // Getters
  std::pair<int, int> getPixelPosition() const;
  std::pair<int, int> getBoardPosition() const;
  int getSize() const;

private:
  // Used to control the cell's color
  SDL_Texture* cell;
  // Determines size and location to render at
  SDL_Rect container;
};