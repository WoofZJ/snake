#ifndef GAME_H
#define GAME_H

#include <cstdint>
#include <deque>

enum Direction {
  Up,
  Left,
  Right,
  Down
};

enum GameStatus {
  Gaming,
  Win,
  Lose
};

struct Position {
  int32_t x, y;
  bool operator ==(const Position other) {
    return x == other.x && y == other.y;
  }
  bool operator !=(const Position other) {
    return x != other.x || y != other.y;
  }
};

class Game {
public:
  Game(uint32_t width, uint32_t height);
  void forward();
  void input(Direction dir);
  void render();
  GameStatus getStatus();

private:
  bool generateFood();
  void check();

private:
  std::deque<Position> m_snake;
  uint32_t m_width, m_height;
  uint32_t m_length;
  Position m_food_pos;
  Direction m_dir;
  GameStatus m_status;
};

#endif