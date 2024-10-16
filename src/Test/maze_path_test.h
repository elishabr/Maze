#ifndef TEST_MAZE
#include <gtest/gtest.h>

#include "../Maze/Model/fileopen.h"
#include "../Maze/Model/maze_generation.h"
#include "../Maze/Model/maze_path_finding.h"
#define TEST_MAZE
#endif
//Тест - корректная матрица
TEST(MazePathFinding, PathTest1) {
  s21::MazeGeneration maze((size_t)3, (size_t)3);
  maze.Generate();
  s21::Matrix matrixH_Walls = maze.GetHorizontalWalls();
  s21::Matrix matrixW_Walls = maze.GetVerticalWalls();
  EXPECT_EQ(maze.GetRows(), (size_t)3);
  EXPECT_EQ(maze.GetCols(), (size_t)3);
  s21::MazePathFinding path1(matrixW_Walls, matrixH_Walls);
  std::vector<s21::Point> result1 =
      path1.Solver(s21::Point(0, 0), s21::Point(2, 2));
}