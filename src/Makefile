
.PHONY : all clean test clang valgrind gcov_report rebuild

CC=g++
CFLAGS= -Werror -Wextra -Wall
CPPFLAGS=-lstdc++ -std=c++17
TEST_FLAGS:=$(CFLAGS) -g #-fsanitize=address -O1 -fno-omit-frame-pointer
LINUX_FLAGS =-lrt -lpthread -lm -lsubunit
GCOV_FLAGS?=--coverage#-fprofile-arcs -ftest-coverage
LIBS=-lgtest
VALGRIND_FLAGS=--trace-children=yes --track-fds=yes --track-origins=yes --leak-check=full --show-leak-kinds=all --verbose
HEADER=s21_containers.h
TEST_SRC=unit_tests.cc

OS := $(shell uname -s)
USERNAME=$(shell whoami)



ifeq ($(OS),Linux)
  OPEN_CMD = xdg-open
endif
ifeq ($(OS),Darwin)
	OPEN_CMD = open
endif

all: test gcov_report

rebuild:
	make clean
	make all

test: 
ifeq ($(OS), Darwin)
	$(CC) $(TEST_FLAGS) $(LIBS) $(CPPFLAGS) $(TEST_SRC) -o unit_test
else
	${CC} $(TEST_FLAGS) ${TEST_SRC} $(CPPFLAGS) -o unit_test $(LIBS) $(LINUX_FLAGS)
endif
	./unit_test


test_plus: 
ifeq ($(OS), Darwin)
	$(CC) $(TEST_FLAGS) $(LIBS) $(CPPFLAGS) plus_tests.cc -o unit_test
else
	${CC} $(TEST_FLAGS) plus_tests.cc $(CPPFLAGS) -o unit_test_plus $(LIBS) $(LINUX_FLAGS)
endif
	./unit_test_plus

gcov_report: clean
ifeq ($(OS), Darwin)
	$(CC) $(TEST_FLAGS) $(GCOV_FLAGS) $(LIBS) $(CPPFLAGS) $(TEST_SRC) -o gcov_report 
else
	$(CC) $(TEST_FLAGS) $(GCOV_FLAGS) $(TEST_SRC) -o gcov_report $(LIBS) $(CPPFLAGS) $(LINUX_FLAGS)
	$(CC) $(TEST_FLAGS) $(GCOV_FLAGS) plus_tests.cc -o gcov_report_plus $(LIBS) $(CPPFLAGS) $(LINUX_FLAGS)
endif
	./gcov_report
	./gcov_report_plus
	lcov -t "stest" -o s21_test.info -c -d ./ --no-external
	genhtml -o report s21_test.info
	$(OPEN_CMD) ./report/index.html

clang:
	cp ../materials/linters/.clang-format ../src/.clang-format
	clang-format -style=Google -n unit_tests.cc s21_containers/s21_containers.h \
	s21_containers/vector/* s21_containers/list/* s21_containers/queue/* \
	s21_containers/stack/* s21_containers/setMap/avlTree/* \
	s21_containers/setMap/iterators/* s21_containers/setMap/Map/* \
	s21_containers/setMap/Set/*
	rm .clang-format

leaks: test
	leaks -atExit -- ./unit_test

clean_obj:
	rm -rf *.o

clean_lib: 
	rm -rf *.a

clean_test:
	rm -rf *.gcda
	rm -rf *.gcno
	rm -rf *.info
	rm -rf test
	rm -rf report
	rm -rf gcov_report
	rm -rf gcov_report_plus
	rm -rf valgrind_test
	rm -rf *.dSYM

clean: clean_lib clean_lib clean_test clean_obj
	rm -rf unit_test
	rm -rf unit_test_plus
	rm -rf RESULT_VALGRIND.txt
