#include "tetris/headers/Tetris.h"

int main() {
  Tetris tetris;
  
  if (tetris.init()) {
    tetris.run();
  }

  tetris.cleanup();
}