#ifndef FILEOPEN_H
#define FILEOPEN_H

#include <string>

#include "maze.h"

namespace s21 {
class FileOpen {
 public:
  FileOpen(){};
  ~FileOpen(){};

  int parseMatrices(const std::string &fileContent);
  const Matrix &getRightWalls() const;
  const Matrix &getBottomWalls() const;
  int getSizeRow() const;
  int getSizeCol() const;

 private:
  void initializeVariables();
  void parseLine(const std::string &line);
  void handleEmptyLine();
  void validateValue(int value);
  int getError();

  Matrix rightWalls_{};
  Matrix bottomWalls_{};
  int sizeRow_ = 0;
  int sizeCol_ = 0;

  bool errorSize_ = false;
  bool errorOpen_ = false;
  bool errorMatrix_ = false;
  bool errorLineEmpty_ = false;

  bool isFirstMatrix_ = true;
  int countLine_ = 0;
  int countLineEmpty_ = 0;
};
}  // namespace s21
#endif  // FILEOPEN_H
