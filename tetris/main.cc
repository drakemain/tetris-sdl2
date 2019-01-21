#include "tetris/headers/Tetris.h"
#include <string>

int main(int argc, char* argv[]) {
  bool devMode = false;

  for (int i = 0; i < argc; ++i) {
    std::string arg(argv[i]);
    
    if (arg == "dev") {
      devMode = true;
    }
  }

  Tetris tetris(devMode);
  
  if (tetris.init(1)) {
    tetris.run();
  }

  tetris.cleanup();
}