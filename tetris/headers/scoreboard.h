#pragma once
#include <SDL_ttf.h>
#include <vector>
#include <unordered_map>
#include "tetris/headers/Base.h"

// TODO: Render inside viewport

class Scoreboard : public Base {
public:
  Scoreboard(const char* fontPath);
  ~Scoreboard();

  void init(std::vector<class Player*>& players);

  void setPosition(int x, int y);

  void setWidth(int w);
  void setHeight(int h);

  void update(std::vector<Player*> players);
  void update(Player* player);

  void render();
private:
  void draw();
  void draw(Player* player);

  class SDL_Rect container;
  TTF_Font* font;
  std::unordered_map<class Player*, unsigned int> scores;
  std::unordered_map<class Player*, class SDL_Texture*> textures;
};