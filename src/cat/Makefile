NAME=s21_cat

CC=gcc
FLAGS=-Wall -Wextra -Werror -std=c11
LDFLAGS=-o
TEST_EXECUTABLE=testing
TFLAGS=$(TEST_EXECUTABLE) -lcheck
CODE_STYLE=Google
UNAME_S := $(shell uname)

ifeq ($(UNAME_S), Linux)
	TFLAGS += -lm -lsubunit
endif

SRCS := $(shell find . -name "*.c" | grep -v "unittests.c")
OBJS := $(patsubst ./%,%,$(SRCS:.c=.o))

all: $(NAME)

%.o: %.c
	$(CC) $(FLAGS) -c $< $(LDFLAGS) $@

$(NAME): $(OBJS)
	$(CC) $^ $(LDFLAGS) $@

test: _test-compile _test-run

gcov_report: _add-coverage test _gcov

clean:
	rm -rf docs report
	rm -f *.a *.o *.gcda *.gcno *.gcov *.info *.html *.log *.xml *.txt tests_check/_unittests.check $(NAME) $(TEST_EXECUTABLE)

include ../makefiles/util.mk
include ../makefiles/test.mk
include ../makefiles/check.mk
include ../makefiles/cppcheck.mk
include ../makefiles/gcov.mk
include ../makefiles/valgrind.mk
include ../makefiles/style.mk
include ../makefiles/debugging.mk
include ../makefiles/lizard.mk
include ../makefiles/flawfinder.mk
include ../makefiles/doxygen.mk
include ../makefiles/shellcheck.mk

.PHONY: _unittests.check
