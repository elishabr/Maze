#include "fileopen.h"

#include <sstream>

int s21::FileOpen::parseMatrices(const std::string &fileContent) {
  if (fileContent == "") {
    errorOpen_ = true;
    return getError();
  }

  initializeVariables();
  std::istringstream stream(fileContent);
  std::string line;
  while (std::getline(stream, line)) {
    parseLine(line);
    if (errorSize_ || errorMatrix_ || errorLineEmpty_) return getError();
  }

  if (countLine_ - (sizeRow_ + 1) != sizeRow_) {
    errorSize_ = true;
  }
  return getError();
}

void s21::FileOpen::initializeVariables() {
  rightWalls_.clear();
  bottomWalls_.clear();
  sizeCol_ = 0;
  sizeRow_ = 0;
  isFirstMatrix_ = true;
  countLine_ = 0;
  countLineEmpty_ = 0;
}

void s21::FileOpen::parseLine(const std::string &line) {
  if (line.empty()) {
    handleEmptyLine();
    return;
  }
  if (countLineEmpty_ > 1) {
    errorLineEmpty_ = true;
    return;
  }

  std::vector<int> row;
  int value = 0;
  int countValue = 0;
  std::istringstream iss(line);
  while (iss >> value) {
    countValue++;
    validateValue(value);
    if (countLine_ != 0) row.push_back(value);
  }
  if (countValue != sizeCol_ && countLine_ != 0) {
    errorSize_ = true;
    return;
  }
  if (isFirstMatrix_ && countLine_ != 0) {
    rightWalls_.push_back(row);
  } else if (countLine_ != 0) {
    bottomWalls_.push_back(row);
  }
  countLine_++;
}

void s21::FileOpen::handleEmptyLine() {
  if (countLine_ - 1 != sizeRow_) {
    errorSize_ = true;
    return;
  }
  countLineEmpty_++;
  isFirstMatrix_ = false;
}

void s21::FileOpen::validateValue(int value) {
  if (countLine_ == 0) {
    if (value > 50 || value < 1) {
      errorSize_ = true;
      return;
    }
    if (sizeRow_ == 0) {
      sizeRow_ = value;
    } else {
      sizeCol_ = value;
    }
  } else {
    if (value != 1 && value != 0) {
      errorMatrix_ = true;
      return;
    }
  }
}

int s21::FileOpen::getError() {
  if (errorOpen_ || errorLineEmpty_ || errorSize_ || errorMatrix_) {
    initializeVariables();
    if (errorOpen_) {
      errorOpen_ = false;
      return 4;
    } else if (errorLineEmpty_) {
      errorLineEmpty_ = false;
      return 3;
    } else if (errorSize_) {
      errorSize_ = false;
      return 2;
    } else {
      errorMatrix_ = false;
      return 1;
    }
  } else {
    return 0;
  }
}

const s21::Matrix &s21::FileOpen::getRightWalls() const { return rightWalls_; }

const s21::Matrix &s21::FileOpen::getBottomWalls() const {
  return bottomWalls_;
}

int s21::FileOpen::getSizeRow() const { return sizeRow_; }

int s21::FileOpen::getSizeCol() const { return sizeCol_; }
