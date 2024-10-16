#ifndef FINDING_MAZE_PATH_FINDING_H_
#define FINDING_MAZE_PATH_FINDING_H_

#include "maze.h"

namespace s21 {
class MazePathFinding {
 public:
  MazePathFinding(const Maze& maze);
  MazePathFinding(const Matrix& vertical_wall, const Matrix& horizontal_wall);
  std::vector<Point> Solver(const Point& start_point, const Point& end_point);

 private:
  Maze maze_;

  bool ValidateIndices(int row, int col) const;
  bool CanMove(const Point& start, const Point& end, int dx, int dy);
  void MakePath(const Matrix& answer, std::vector<Point>& path,
                const Point& start_point, const Point& end_point);
};

}  // namespace s21

#endif  // FINDING_MAZE_PATH_FINDING_H_
