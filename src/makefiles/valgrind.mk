_valgrind: _dir-report
	valgrind --leak-check=full --show-reachable=yes --track-fds=yes --log-file=report/valgrind.log ./$(TEST_EXECUTABLE)
	tail -n 8 report/valgrind.log

test-valgrind: clean unittests _test-compile _valgrind

test-valgrind_ci: test-valgrind
	if grep -q "ERROR SUMMARY: 0 errors from 0 contexts" ./report/valgrind.log; then \
		exit 0; \
	else \
		exit 1; \
	fi
