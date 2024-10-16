#include "file_open_test.h"
#include "maze_gener_test.h"
#include "maze_path_test.h"

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
