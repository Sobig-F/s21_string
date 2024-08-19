NAME      := s21_string
CC        := gcc
CFLAGS    := -std=c11 -pedantic -Wall -Werror -Wextra
GCOVFLAGS := -fprofile-arcs -ftest-coverage
LIBR      := $(NAME).a
SRC       := $(NAME).c
OBJ       := $(NAME).o
HEADER    := $(NAME).h
TEST      := test_$(NAME).c
OS        := $(shell uname -s)

ifeq ($(OS), Linux)
	CFLAGS+=           -D OS_LINUX
	CHECKFLAGS=        -lcheck -lpthread -pthread -lrt -lsubunit
	OPEN_CMD=          xdg-open
endif
ifeq ($(OS), Darwin)
	CFLAGS+=           -D OS_MAC
	CHECKFLAGS=        $(shell pkg-config --cflags --libs check)
	OPEN_CMD=          open
endif

.PHONY: all clean test gcov_report # объявляет цели фиктивными, чтобы компилятор не искал эти файлы

all: clean $(LIBR)

$(LIBR): sscanf.o sprintf.o $(OBJ)
	ar rcs $(LIBR) $(OBJ) sscanf.o sprintf.o
	rm -rf ./*.o

$(OBJ): $(SRC) $(HEADER)
	$(CC) -c $(SRC) -o $(OBJ) $(CFLAGS)

sscanf.o: s21_sscanf.c s21_sscanf.h
	$(CC) -c s21_sscanf.c -o sscanf.o $(CFLAGS)

sprintf.o: s21_sprintf.c s21_sprintf.h
	$(CC) -c s21_sprintf.c -o sprintf.o $(CFLAGS)

test: rebuild_lib $(TEST)
	$(CC) $(CFLAGS) $(TEST) $(LIBR) $(CHECKFLAGS) -lm -Wno-gnu-zero-variadic-macro-arguments -o test
	./test

gcov_report: rebuild_lib
	$(CC) $(GCOVFLAGS) $(TEST) $(SRC) s21_sscanf.c s21_sprintf.c $(CHECKFLAGS) -lm -o GcovReport
	./GcovReport
	lcov -t "GcovReport" -o GcovReport.info -c -d .
	genhtml -o gcov_report GcovReport.info
	rm -rf ./*.gcno ./*gcda ./GcovReport
	$(OPEN_CMD) ./gcov_report/index.html

clean:
	rm -f $(LIBR) $(OBJ) $(NAME) *.gc*
	rm -rf gcov_report test GcovReport GcovReport.info

rebuild_lib: clean $(LIBR)

cn:
	clang-format -n -style=Google *.c *.h
