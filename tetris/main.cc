#include "tetris/headers/Tetris.h"
#include <string>

int main(int argc, char* argv[]) {
  bool devMode = false;
  int players = 1;

  for (int i = 0; i < argc; ++i) {
    std::string arg(argv[i]);
    
    if (arg == "dev") {
      devMode = true;
    } else if (arg == "players") {
      players = std::stoi(argv[++i]);
    }
  }

  Tetris tetris(devMode);
  
  if (tetris.init(players)) {
    tetris.run();
  }

  tetris.cleanup();
}