_gcov:
	lcov -t "$(TEST_EXECUTABLE)" -o coverage.info -c -d .
	genhtml -o report coverage.info

_add-coverage:
	$(eval FLAGS += --coverage)
	$(eval TFLAGS += --coverage)

test-gcov: clean unittests _add-coverage test _gcov

test-gcov_ci: clean _add-coverage test _gcov
	lcov -t "$(TEST_EXECUTABLE)" -o coverage.info -c -d .
	genhtml -o report coverage.info
	@COVERAGE=$$(lcov --summary coverage.info 2>&1 | grep 'lines......:' | awk -F" " '{print $$2}' | tr -d '%') ;\
	COVERAGE_INT=$$(printf "%.0f" $$COVERAGE) ;\
	if [ $$COVERAGE_INT -lt 80 ]; then \
			echo "Code coverage is $$COVERAGE%, which is below the allowed limit of 80%." ;\
			exit 1 ;\
	else \
			echo "Code coverage is $$COVERAGE%, which is above the allowed limit of 80%." ;\
	fi
