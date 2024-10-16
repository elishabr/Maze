
#ifndef TEST_MAZE
#include <gtest/gtest.h>

#include <fstream>

#include "../Maze/Model/fileopen.h"
#include "../Maze/Model/maze_generation.h"
#include "../Maze/Model/maze_path_finding.h"
#define TEST_MAZE
#endif
//Тест - корректная матрица
std::string readFileToString(const std::string& filename) {
  std::ifstream file(filename);
  if (!file.is_open()) {
    std::cerr << "Не удалось открыть файл: " << filename << std::endl;
    return "";
  }

  // Используем std::string для хранения содержимого файла
  std::string content((std::istreambuf_iterator<char>(file)),
                      std::istreambuf_iterator<char>());

  file.close();
  return content;
}

TEST(FileOpen, ParseTest1) {
  s21::FileOpen parser;
  std::string fileContent = readFileToString("Test/file.txt");
  int errorParser = parser.parseMatrices(fileContent);
  s21::Matrix matrixR_Walls = parser.getRightWalls();
  s21::Matrix matrixB_Walls = parser.getBottomWalls();
  EXPECT_EQ(errorParser, 0);
  EXPECT_EQ(parser.getSizeCol(), 4);
  EXPECT_EQ(parser.getSizeRow(), 4);
}
//Тест - ошибка в размерности матрицы
TEST(FileOpen, ParseTest2) {
  s21::FileOpen parser;
  std::string fileContent = readFileToString("Test/file1.txt");
  int errorParser = parser.parseMatrices(fileContent);
  s21::Matrix matrixR_Walls = parser.getRightWalls();
  s21::Matrix matrixB_Walls = parser.getBottomWalls();
  EXPECT_EQ(errorParser, 2);
  EXPECT_EQ(parser.getSizeCol(), 0);
  EXPECT_EQ(parser.getSizeRow(), 0);
}
//Тест - ошибку в матрице
TEST(FileOpen, ParseTest3) {
  s21::FileOpen parser;
  std::string fileContent = readFileToString("Test/file2.txt");
  int errorParser = parser.parseMatrices(fileContent);
  s21::Matrix matrixR_Walls = parser.getRightWalls();
  s21::Matrix matrixB_Walls = parser.getBottomWalls();
  EXPECT_EQ(errorParser, 1);
  EXPECT_EQ(parser.getSizeCol(), 0);
  EXPECT_EQ(parser.getSizeRow(), 0);
}
//Тест - лишний пробел в файле
TEST(FileOpen, ParseTest4) {
  s21::FileOpen parser;
  std::string fileContent = readFileToString("Test/file3.txt");
  int errorParser = parser.parseMatrices(fileContent);
  s21::Matrix matrixR_Walls = parser.getRightWalls();
  s21::Matrix matrixB_Walls = parser.getBottomWalls();
  EXPECT_EQ(errorParser, 3);
  EXPECT_EQ(parser.getSizeCol(), 0);
  EXPECT_EQ(parser.getSizeRow(), 0);
}
//Тест -  некорректный файл
TEST(FileOpen, ParseTest5) {
  s21::FileOpen parser;
  std::string fileContent = readFileToString("not_file.txt");
  std::cout << fileContent << std::endl;
  int errorParser = parser.parseMatrices(fileContent);
  s21::Matrix matrixR_Walls = parser.getRightWalls();
  s21::Matrix matrixB_Walls = parser.getBottomWalls();
  EXPECT_EQ(errorParser, 4);
  EXPECT_EQ(parser.getSizeCol(), 0);
  EXPECT_EQ(parser.getSizeRow(), 0);
}

// Tест - недопустимый размер матрицы
TEST(FileOpen, ParseTest6) {
  s21::FileOpen parser;
  std::string fileContent = readFileToString("Test/file5.txt");
  int errorParser = parser.parseMatrices(fileContent);
  s21::Matrix matrixR_Walls = parser.getRightWalls();
  s21::Matrix matrixB_Walls = parser.getBottomWalls();
  EXPECT_EQ(errorParser, 2);
  EXPECT_EQ(parser.getSizeCol(), 0);
  EXPECT_EQ(parser.getSizeRow(), 0);
}