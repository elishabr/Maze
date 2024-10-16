#ifndef MAZE_GENERATION_H_
#define MAZE_GENERATION_H_

#include <string>
#include <unordered_map>

#include "maze.h"

namespace s21 {

class MazeGeneration {
 public:
  MazeGeneration();
  MazeGeneration(size_t rows, size_t cols);

  void Generate();
  void SaveFile(std::string& fileContent) const;

  const Matrix& GetVerticalWalls() const;
  const Matrix& GetHorizontalWalls() const;

  size_t GetRows() const;
  size_t GetCols() const;

 private:
  Maze maze_;

  size_t counter_ = 1;
  std::vector<int> line_;
  std::unordered_map<int, int> count_elements_sets_;

  void SetUniqueValue();
  void AddingRightWalls(size_t row);
  void AddingLowerWalls(size_t row);
  void PreparatingNewLine(size_t row);
  void AddingEndLine(size_t row);

  bool RandomValue();
};

}  // namespace s21

#endif  // MAZE_GENERATION_H_
