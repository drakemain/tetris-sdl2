#include "tetris/headers/Tetris.h"
#include "tetris/headers/tetromino.h"

int main() {
  Tetris tetris;
  Tetromino(tetris.getRenderer());
  if (tetris.init()) {
    tetris.run();
  }

  tetris.cleanup();
}