#ifndef A1_MAZE_CPP_SRC_MODEL_MAZE_H_
#define A1_MAZE_CPP_SRC_MODEL_MAZE_H_

#include <cstddef>
#include <vector>

namespace s21 {

using Matrix = std::vector<std::vector<int>>;
using Point = std::pair<int, int>;

struct Maze {
  Maze() : Maze(0, 0) {}

  Maze(size_t rows, size_t cols)
      : rows_(rows),
        cols_(cols),
        vertical_wall_(rows, std::vector<int>(cols, 1)),
        horizontal_wall_(rows, std::vector<int>(cols, 1)) {}

  Maze(const Matrix& vertical_wall, const Matrix& horizontal_wall)
      : rows_(vertical_wall.size()),
        cols_((vertical_wall.size() == 0 ? 0 : vertical_wall[0].size())),
        vertical_wall_(vertical_wall),
        horizontal_wall_(horizontal_wall) {}

  size_t rows_;
  size_t cols_;
  Matrix vertical_wall_;
  Matrix horizontal_wall_;
};

}  // namespace s21

#endif  // A1_MAZE_CPP_SRC_MODEL_MAZE_H_
