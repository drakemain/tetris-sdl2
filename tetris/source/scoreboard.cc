#include "tetris/headers/scoreboard.h"
#include "tetris/headers/player.h"
#include <iostream>

Scoreboard::Scoreboard(const char* fontPath) {
  this->font = TTF_OpenFont(fontPath, 32);

  if (!this->font) {
    printf("Scoreboard failed to load font %s. %s", fontPath, TTF_GetError());
  }
}

Scoreboard::~Scoreboard() {
  TTF_CloseFont(this->font);

  for (std::pair<Player*, SDL_Texture*> t : this->textures) {
    SDL_DestroyTexture(t.second);
  }
}

void Scoreboard::init(std::vector<Player*>& players) {
  this->scores.reserve(players.size());
  this->textures.reserve(players.size());
  
  for (size_t i = 0; i < players.size(); ++i) {
    this->scores[players[i]] = players[i]->getScore();
  }

  this->draw();
}

void Scoreboard::setPosition(int x, int y) {
  printf("Pos: (%d, %d)\n", x, y);

  this->container.x = x;
  this->container.y = y;
}

void Scoreboard::setWidth(int w) {
  if (w < 0) {
    w = 0;
  }

  this->container.w = w;
}

void Scoreboard::setHeight(int h) {
  if (h < 0) {
    h = 0;
  }

  this->container.h = h;
}

void Scoreboard::update(std::vector<Player*> players) {
  for (Player* player : players) {
    unsigned int score = player->getScore();
    
    if (score != this->scores[player]) {
      this->scores[player] = score;
      this->draw(player);
    }
  }
}

void Scoreboard::update(Player* player) {
  if (player) {
    unsigned int score = player->getScore();

    if (score != this->scores[player]) {
      this->scores[player] = score;
      this->draw(player);
    }
  }
}

void Scoreboard::draw() {
  for (std::pair<Player*, unsigned int> score : this->scores) {
    this->draw(score.first);
  }
}

void Scoreboard::draw(Player* player) {
  if (this->textures[player]) {
    SDL_DestroyTexture(this->textures[player]);
  }

  std::string text = "Player " + std::to_string(player->id + 1) + ": " + std::to_string(player->getScore());
  
  SDL_Surface* surface = TTF_RenderText_Solid(this->font, text.c_str(), {255, 255, 255, 255});
  this->textures[player] = SDL_CreateTextureFromSurface(this->getRenderer(), surface);

  SDL_FreeSurface(surface);
}

void Scoreboard::render() {
  if (this->container.w == 0 || this->container.h == 0) { return; }

  size_t textureCounter = 0;
  size_t textureHeight = this->container.h / this->textures.size();

  for (std::pair<Player*, SDL_Texture*> t : this->textures) {
    SDL_Texture* texture = t.second;

    if (texture) {
      SDL_Rect container;
      container.x = this->container.x;
      container.y = this->container.y + (textureHeight * textureCounter);
      container.w = this->container.w;
      container.h = textureHeight;
      SDL_RenderCopy(this->getRenderer(), texture, NULL, &container);
      ++textureCounter;
    }
  }
}