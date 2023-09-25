#include <vector>
#include <algorithm>
#include <ctime>
#include <cstdlib>
#include "raylib.h"
#include "game.h"

Game::Game(uint32_t width, uint32_t height)
  : m_width(width), m_height(height), m_dir(Down), m_length(1), m_status(Gaming)
{
  m_snake.push_front({0, 0});
  srand(time(0));
  generateFood();
}

void Game::forward() {
  int32_t dx = 0, dy = 0;
  Position head = m_snake.front();

  switch (m_dir)
  {
    case Up:    dy = -1; break;
    case Left:  dx = -1; break;
    case Right: dx =  1; break;
    case Down:  dy =  1; break;
  }
  head.x += dx;
  head.y += dy;
  m_snake.push_front(head);
  if (m_food_pos != head) {
    m_snake.pop_back();
  }
  check();
}

void Game::input(Direction dir) {
  if (dir + m_dir != 3) {
    m_dir = dir;
  }
}

void Game::check() {
  if (m_food_pos == m_snake.front() && !generateFood()) {
    m_status = Win;
  } else {
    for (auto iter = ++m_snake.begin(); iter != m_snake.end(); ++iter) {
      if (*iter == m_snake.front()) {
        m_status = Lose;
        return;
      }
    }
    auto [x, y] = m_snake.front();
    if (x < 0 || y < 0 || x >= m_width || y >= m_height) {
        m_status = Lose;
        return;
    }
  }
}

bool Game::generateFood() {
  std::vector<Position> available;
  for (int32_t i = 0; i < m_width; ++i) {
    for (int32_t j = 0; j < m_height; ++j) {
      if (std::find(m_snake.begin(), m_snake.end(), Position{i, j}) == m_snake.end()) {
        available.push_back({i, j});
      }
    }
  }
  if (std::empty(available)) {
    m_status = Win;
    return false;
  }
  printf("%zu\n", available.size());
  m_food_pos = available.at(rand() % available.size());
  return true;
}

GameStatus Game::getStatus() {
  return m_status;
}

void Game::render() {
  int w = GetRenderWidth(), h = GetRenderHeight();
  BeginDrawing();
  ClearBackground(WHITE);
  if (m_status == Gaming) {
    for (auto pos: m_snake) {
      DrawRectangle(pos.x*w/m_width, pos.y*h/m_height, w/m_width-2, h/m_height-2, GREEN);
    }
    DrawCircle((m_food_pos.x+0.5)*w/m_width, (m_food_pos.y+0.5)*h/m_height, w/m_width/2-1, RED);
  } else {
    switch (m_status) {
      case Win:
        ClearBackground({130, 0, 0, 255});
        break;
      case Lose:
        ClearBackground({0, 0, 130, 255});
        break;
    }
  }

  EndDrawing();
}