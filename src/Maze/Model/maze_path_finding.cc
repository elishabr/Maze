#include "maze_path_finding.h"

#include <algorithm>
#include <queue>

using namespace s21;

MazePathFinding::MazePathFinding(const Maze& maze)
    : maze_(maze.vertical_wall_, maze.horizontal_wall_) {}

MazePathFinding::MazePathFinding(const Matrix& vertical_wall,
                                 const Matrix& horizontal_wall)
    : maze_(vertical_wall, horizontal_wall) {}

std::vector<Point> MazePathFinding::Solver(const Point& start_point,
                                           const Point& end_point) {
  Matrix answer(maze_.rows_, std::vector<int>(maze_.cols_, 0));
  std::vector<Point> path;

  std::queue<Point> points;
  points.push(start_point);
  answer[start_point.first][start_point.second] = 1;

  std::vector<int> dx{-1, 0, 0, 1};
  std::vector<int> dy{0, -1, 1, 0};

  while (!points.empty()) {
    Point point = points.front();
    points.pop();

    for (size_t i = 0; i < 4; ++i) {
      int x = point.first + dx[i];
      int y = point.second + dy[i];

      if (ValidateIndices(x, y) && answer[x][y] == 0) {
        if (CanMove(point, {x, y}, dx[i], dy[i])) {
          points.push({x, y});
          answer[x][y] = answer[point.first][point.second] + 1;
        }
      }
    }
  }

  MakePath(answer, path, start_point, end_point);

  return path;
}

void MazePathFinding::MakePath(const Matrix& answer, std::vector<Point>& path,
                               const Point& start_point,
                               const Point& end_point) {
  Point current_point = end_point;
  path.push_back(current_point);

  std::vector<int> dx{-1, 0, 0, 1};
  std::vector<int> dy{0, -1, 1, 0};

  while (current_point != start_point) {
    for (size_t i = 0; i < 4; ++i) {
      int x = current_point.first + dx[i];
      int y = current_point.second + dy[i];

      if (ValidateIndices(x, y) &&
          answer[x][y] ==
              answer[current_point.first][current_point.second] - 1) {
        if (CanMove(current_point, {x, y}, dx[i], dy[i])) {
          current_point = {x, y};
          path.push_back(current_point);
        }
      }
    }
  }
  std::reverse(path.begin(), path.end());
}

bool MazePathFinding::ValidateIndices(int row, int col) const {
  if (row < 0 || row >= static_cast<int>(maze_.rows_) || col < 0 ||
      col >= static_cast<int>(maze_.cols_)) {
    return false;
  }

  return true;
}

bool MazePathFinding::CanMove(const Point& start, const Point& end, int dx,
                              int dy) {
  if (dx == -1 && dy == 0 &&
      maze_.horizontal_wall_[end.first][end.second] == 0) {
    return true;

  } else if (dx == 1 && dy == 0 &&
             maze_.horizontal_wall_[start.first][start.second] == 0) {
    return true;

  } else if (dx == 0 && dy == -1 &&
             maze_.vertical_wall_[end.first][end.second] == 0) {
    return true;

  } else if (dx == 0 && dy == 1 &&
             maze_.vertical_wall_[start.first][start.second] == 0) {
    return true;
  }

  return false;
}
