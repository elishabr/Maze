
#ifndef TEST_MAZE
#include <gtest/gtest.h>

#include "../Maze/Model/fileopen.h"
#include "../Maze/Model/maze_generation.h"
#include "../Maze/Model/maze_path_finding.h"
#define TEST_MAZE
#endif

TEST(MazeGeneration, GenerTest1) {
  s21::MazeGeneration maze((size_t)3, (size_t)3);
  maze.Generate();
  s21::Matrix matrixH_Walls = maze.GetHorizontalWalls();
  s21::Matrix matrixW_Walls = maze.GetVerticalWalls();
  EXPECT_EQ(maze.GetRows(), (size_t)3);
  EXPECT_EQ(maze.GetCols(), (size_t)3);
}

TEST(MazeGeneration, GenerTest2) {
  s21::MazeGeneration maze((size_t)10, (size_t)30);
  maze.Generate();
  s21::Matrix matrixH_Walls = maze.GetHorizontalWalls();
  s21::Matrix matrixW_Walls = maze.GetVerticalWalls();
  EXPECT_EQ(maze.GetRows(), (size_t)10);
  EXPECT_EQ(maze.GetCols(), (size_t)30);
}
//Тест - сохранение файла
TEST(MazeGeneration, GenerTest3) {
  s21::MazeGeneration maze((size_t)50, (size_t)50);
  maze.Generate();
  s21::Matrix matrixH_Walls = maze.GetHorizontalWalls();
  s21::Matrix matrixW_Walls = maze.GetVerticalWalls();
  std::string fileContent;
  maze.SaveFile(fileContent);
  EXPECT_EQ(maze.GetRows(), (size_t)50);
  EXPECT_EQ(maze.GetCols(), (size_t)50);
}
//Тест - некорректный файл
TEST(MazeGeneration, GenerTest4) {
  s21::MazeGeneration maze((size_t)50, (size_t)50);
  maze.Generate();
  s21::Matrix matrixH_Walls = maze.GetHorizontalWalls();
  s21::Matrix matrixW_Walls = maze.GetVerticalWalls();
  std::string fileContent;
  maze.SaveFile(fileContent);
  EXPECT_EQ(maze.GetRows(), (size_t)50);
  EXPECT_EQ(maze.GetCols(), (size_t)50);
}