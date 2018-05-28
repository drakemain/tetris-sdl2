#include "tetris/headers/Tetris.h"
#include "tetris/headers/cell.h"

int main() {
  Tetris tetris;
  
  if (tetris.init()) {
    tetris.run();
  }

  tetris.cleanup();
}