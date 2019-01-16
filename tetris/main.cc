#include "tetris/headers/Tetris.h"

int main(int argc, char* argv[]) {
  bool devMode = false;

  for (int i = 0; i < argc; ++i) {
    std::string arg(argv[i]);
    
    if (arg == "dev") {
      devMode = true;
    }
  }

  Tetris tetris(devMode);
  
  if (tetris.init()) {
    tetris.run();
  }

  tetris.cleanup();
}