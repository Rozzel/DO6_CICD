SRCS_TEST=$(shell find . -name "*.c" | grep -v "main.c")
OBJS_TEST=$(patsubst ./%,%,$(SRCS_TEST:.c=.o))

_add-pedantic:
	$(eval FLAGS += -Wpedantic)
	$(eval FLAGS += -pedantic)

_test-compile: $(OBJS_TEST)
	$(CC) $(FLAGS) $^ $(LDFLAGS) $(TFLAGS)

_test-run:
	./$(TEST_EXECUTABLE)

rebuild: clean $(NAME)

test-start: clean unittests _add-pedantic test-style test-cppcheck test-lizard test-flawfinder _test-compile _test-run

test-bash: clean all
	./tests_bash/main.sh

test-bash_debug:
	bash -x ./tests_bash/main.sh 1 > test_bash.log 2>&1
