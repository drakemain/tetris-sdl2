#include "tetris/headers/scoreboard.h"
#include "tetris/headers/player.h"
#include <iostream>

using PlayerToTexture = std::pair<class Player*, std::pair<class SDL_Texture*, class SDL_Rect>>;

Scoreboard::Scoreboard(const char* fontPath) {
  this->font = TTF_OpenFont(fontPath, 32);

  if (!this->font) {
    printf("Scoreboard failed to load font %s. %s", fontPath, TTF_GetError());
  }
}

Scoreboard::~Scoreboard() {
  TTF_CloseFont(this->font);

  for (PlayerToTexture t : this->textures) {
    SDL_DestroyTexture(t.second.first);
  }
}

void Scoreboard::init(std::vector<Player*>& players) {
  std::cout << "INIT" << std::endl;
  this->scores.reserve(players.size());
  
  for (size_t i = 0; i < players.size(); ++i) {
    this->scores[players[i]] = 0;
    SDL_Rect container;
    container.x = 525;
    container.y = 100 * i;
    container.w = 500;
    container.h = 100;
    this->textures[players[i]] = {NULL, container};
  }

  this->draw();
}

void Scoreboard::setPosition(int x, int y) {
  this->container.x = x;
  this->container.y = y;
}

void Scoreboard::setWidth(int w) {
  this->container.w = w;
}

void Scoreboard::setHeight(int h) {
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
  std::cout << "DRAW" << std::endl;

  if (this->textures[player].first) {
    SDL_DestroyTexture(this->textures[player].first);
  }

  std::string text = "Player " + std::to_string(player->id) + ": " + std::to_string(player->getScore());
  
  SDL_Surface* surface = TTF_RenderText_Solid(this->font, text.c_str(), {255, 255, 255, 255});
  this->textures[player].first = SDL_CreateTextureFromSurface(this->getRenderer(), surface);

  SDL_FreeSurface(surface);
}

void Scoreboard::render() {
  for (PlayerToTexture t : this->textures) {
    SDL_Texture* texture = t.second.first;

    if (texture) {
      SDL_Rect* container = &t.second.second;
      SDL_RenderCopy(this->getRenderer(), texture, NULL, container);
    }
  }
}