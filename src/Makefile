SHELL = /bin/bash # если на MacOS не работает, замени на /bin/sh

GCC := g++ -Werror -Wextra -Wall --std=c++17 -lstdc++ -lm
SANITIZER :=  -fsanitize=address
SOURSE :=  Test/*.cc Maze/Model/*.cc
FLAGS_LCOV := -g -fprofile-arcs -ftest-coverage
FLAGS_GTEST := -lgtest -lgcov -pthread
OS = $(shell uname)


all: install

install: uninstall
	@mkdir Maze/build
	cd Maze/build && cmake .. && make && rm Makefile
	./Maze/build/Maze
web:
ifeq ($(OS), Darwin)
	@echo "Если не получилось - пожалуйста, установите Python и попробуйте снова."
	cd WebMaze && python -m http.server 3000
else
	sudo apt install python3
	cd WebMaze && python3 -m http.server 3000
endif
open:
	./Maze/build/Maze
uninstall:
	@rm -rf Maze/build
test: clean
	$(GCC) $(FLAGS_LCOV) $(SOURSE) $(FLAGS_GTEST) -o s21_test_maze
	./s21_test_maze
gcov_report: test
#vvvvv
# --ignore-errors mismatch - дополнительный флаг для MacOS
	@lcov  -t test -o rep.info -c -d .
	@genhtml -o report rep.info
	@rm -rf gcovreport gcovreport.info *.gcda *.gcno math_test.gcda math_test.gcno
	@open ./report/index.html
check: test
	clang-format --style=Google -n $(shell find . -name '*.cc') $(shell find . -name '*.h') $(shell find . -name '*.cpp')
	clang-format --style=Google -i $(shell find . -name '*.cc') $(shell find . -name '*.h') $(shell find . -name '*.cpp')
	cppcheck --enable=all --suppress=missingIncludeSystem --inconclusive --check-config Maze/*.*
ifeq ($(OS), Darwin) 
	leaks --atExit -- ./s21_test_maze
else
	CK_FORK=no valgrind --vgdb=no --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose --log-file=RESULT_VALGRIND.txt ./s21_test_maze
endif

dvi:
	open readme.md
dist:
	@rm -rf ../Maze_0-1.0/
	@mkdir ../Maze_0-1.0/
	@mkdir ../Maze_0-1.0/src
ifeq ($(OS), Darwin)
	@cp Maze/build/Maze.app/Contents/MacOS/Maze ../Calc2_0-2.0/src/
else
	@cp Maze/build/Maze ../Maze_0-1.0/src/
endif
	cd .. && tar cvzf Calc2_0-2.0.tgz ./Maze_0-1.0
	
clean:
	rm -rf s21_test_maze
	rm -rf *.o test *.a a.out *.gcno *.gcda s21_test_maze.dSYM *.info report *.gch *.txt
	rm -rf Maze/build
	rm -rf ../Maze_0-1.0/
