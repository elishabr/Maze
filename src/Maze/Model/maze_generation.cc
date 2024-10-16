
#include "maze_generation.h"

#include <algorithm>
#include <iostream>
#include <random>
#include <sstream>

using namespace s21;

MazeGeneration::MazeGeneration() : MazeGeneration(0, 0) {}

MazeGeneration::MazeGeneration(size_t rows, size_t cols)
    : maze_(rows, cols), line_(std::vector<int>(cols)) {}

const Matrix& MazeGeneration::GetVerticalWalls() const {
  return maze_.vertical_wall_;
}

const Matrix& MazeGeneration::GetHorizontalWalls() const {
  return maze_.horizontal_wall_;
}

size_t MazeGeneration::GetRows() const { return maze_.rows_; }
size_t MazeGeneration::GetCols() const { return maze_.cols_; }

void MazeGeneration::Generate() {
  std::fill(line_.begin(), line_.end(), 0);

  for (size_t i = 0; i < maze_.rows_; ++i) {
    SetUniqueValue();

    AddingRightWalls(i);
    AddingLowerWalls(i);

    if (i != maze_.rows_ - 1) {
      PreparatingNewLine(i);
    }
  }
  AddingEndLine(maze_.rows_ - 1);
}

void MazeGeneration::SetUniqueValue() {
  for (size_t i = 0; i < maze_.cols_; ++i) {
    if (line_[i] == 0) {
      line_[i] = counter_;
      ++count_elements_sets_[counter_];
      ++counter_;
    }
  }
}

void MazeGeneration::AddingRightWalls(size_t row) {
  for (size_t i = 0; i < maze_.cols_ - 1; ++i) {
    if (!RandomValue() && line_[i] != line_[i + 1]) {
      maze_.vertical_wall_[row][i] = 0;

      count_elements_sets_[line_[i]] += count_elements_sets_[line_[i + 1]];
      count_elements_sets_[line_[i + 1]] = 0;

      int old_value = line_[i + 1];
      int new_value = line_[i];
      std::replace(line_.begin(), line_.end(), old_value, new_value);
    }
  }
}

void MazeGeneration::AddingLowerWalls(size_t row) {
  std::unordered_map<int, int> elements_with_wall;
  for (size_t i = 0; i < maze_.cols_; ++i) {
    if (!RandomValue() ||
        count_elements_sets_[line_[i]] - elements_with_wall[line_[i]] <= 1) {
      maze_.horizontal_wall_[row][i] = 0;
    } else {
      ++elements_with_wall[line_[i]];
    }
  }
}

void MazeGeneration::PreparatingNewLine(size_t row) {
  for (size_t i = 0; i < maze_.cols_; ++i) {
    if (GetHorizontalWalls()[row][i] == 1) {
      --count_elements_sets_[line_[i]];
      line_[i] = 0;
    }
  }
}

void MazeGeneration::AddingEndLine(size_t row) {
  for (size_t i = 0; i < maze_.cols_; ++i) {
    maze_.horizontal_wall_[row][i] = 1;
  }

  for (size_t i = 0; i < maze_.cols_ - 1; ++i) {
    if (line_[i] != line_[i + 1]) {
      maze_.vertical_wall_[row][i] = 0;

      int old_value = line_[i + 1];
      int new_value = line_[i];
      std::replace(line_.begin(), line_.end(), old_value, new_value);
    }
  }
}

bool MazeGeneration::RandomValue() {
  static std::random_device rd;
  static std::mt19937 gen(rd());

  static std::uniform_int_distribution<> distrib(0, 1);

  return distrib(gen);
}

void MazeGeneration::SaveFile(std::string& fileContent) const {
  std::ostringstream stream;

  stream << maze_.rows_ << " " << maze_.cols_ << std::endl;
  for (size_t i = 0; i < maze_.rows_; ++i) {
    for (size_t j = 0; j < maze_.cols_; ++j) {
      stream << maze_.vertical_wall_[i][j] << " ";
    }
    stream << std::endl;
  }

  stream << std::endl;

  for (size_t i = 0; i < maze_.rows_; ++i) {
    for (size_t j = 0; j < maze_.cols_; ++j) {
      stream << maze_.horizontal_wall_[i][j] << " ";
    }
    stream << std::endl;
  }

  fileContent = stream.str();
}
