#include <ctime>
#include <random>

#include "gol_simulator.hpp"

std::vector<std::vector<int>> NextState(std::vector<std::vector<int>> &state) {
  const int dx[8] = {-1, -1, -1, 0, 0, 1, 1, 1};
  const int dy[8] = {-1, 0, 1, -1, 1, -1, 0, 1};
  const int h = state.size();
  const int w = state[0].size();
  std::vector<std::vector<int>> result(h, std::vector<int>(w, 0));
  
  for (int y = 0; y < h; ++y) {
    for (int x = 0; x < w; ++x) {
      int live = 0;
      for (int i = 0; i < 8; ++i) {
        int kx = x + dx[i];
        int ky = y + dy[i];
        if (kx > 0 && kx < w && ky > 0 && ky < h) {
          if (state[ky][kx] == 1) {
            live++; 
          }
        }
      }
      if ((state[y][x] == 1 && (live == 2 || live == 3)) || (state[y][x] == 0 && live == 3)) {
        result[y][x] = 1; 
      }
      else {
        result[y][x] = 0; 
      }
    }
  }
  return result;
}

std::vector<std::vector<int>> RandomState(const int width, const int height) {
  std::mt19937 rng(time(nullptr));
  
  std::vector<std::vector<int>> result(height, std::vector<int>(width, 0));
  for (int y = 0; y < height; ++y) {
    for (int x = 0; x < width; ++x) {
      result[y][x] = rng()%2;
    }
  }
  
  return result;
}