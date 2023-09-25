#include <iostream>
#include "raylib.h"
#include "game.h"

using namespace std;

int main(int argc, char* argv[]) {
  const uint32_t width = 20, height = 20, size = 50;
  Game game(width, height);

  InitWindow(width*size, height*size, "Snake");

  SetTargetFPS(5);

  while (!WindowShouldClose()) {
    int last_key, key = 0;
    while ((last_key = GetKeyPressed()) != 0) {
      key = last_key;
    }
    if (game.getStatus() == Gaming) {
      game.forward();
    }
    switch (key) {
      case KEY_W:
        game.input(Up);
        break;
      case KEY_A:
        game.input(Left);
        break;
      case KEY_S:
        game.input(Down);
        break;
      case KEY_D:
        game.input(Right);
        break;
      default:
        break;
    }
    game.render();
  }

  return 0;
}
