#include "tetris/headers/Tetris.h"
<<<<<<< HEAD
#include "tetris/headers/tetromino.h"
=======
>>>>>>> master

int main() {
  Tetris tetris;
  Tetromino(tetris.getRenderer());
  if (tetris.init()) {
    tetris.run();
  }

  tetris.cleanup();
}