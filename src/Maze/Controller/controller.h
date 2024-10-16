#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "../Model/fileopen.h"
#include "../Model/maze_generation.h"

//патерн фасад
namespace s21 {
class BaseController {
 public:
  virtual ~BaseController() {}

  // Виртуальные методы, которые будут переопределены в наследниках
  virtual const Matrix& GetRightWalls() const = 0;
  virtual const Matrix& GetBottomWalls() const = 0;
  virtual int GetSizeRow() const = 0;
  virtual int GetSizeCol() const = 0;
};

class FileParserController : public BaseController {
 public:
  FileParserController(FileOpen* model) { fileopen_ = model; }
  ~FileParserController() {}

  int ParseFile(const std::string& filename) {
    return fileopen_->parseMatrices(filename);
  }
  const Matrix& GetRightWalls() const override {
    return fileopen_->getRightWalls();
  }
  const Matrix& GetBottomWalls() const override {
    return fileopen_->getBottomWalls();
  }
  int GetSizeRow() const override { return fileopen_->getSizeRow(); }
  int GetSizeCol() const override { return fileopen_->getSizeCol(); }

 private:
  FileOpen* fileopen_ = nullptr;
};

class MazeGenerationController : public BaseController {
 public:
  MazeGenerationController(int rows, int cols) {
    mazeGen_ = new MazeGeneration(rows, cols);
    mazeGen_->Generate();
  }
  ~MazeGenerationController() { delete mazeGen_; }

  void SaveFile(std::string& file_name) const { mazeGen_->SaveFile(file_name); }
  const Matrix& GetRightWalls() const override {
    return mazeGen_->GetVerticalWalls();
  }
  const Matrix& GetBottomWalls() const override {
    return mazeGen_->GetHorizontalWalls();
  }
  int GetSizeRow() const override { return mazeGen_->GetRows(); }
  int GetSizeCol() const override { return mazeGen_->GetCols(); }

 private:
  MazeGeneration* mazeGen_ = nullptr;
};
}  // namespace s21
#endif  // CONTROLLER_H
