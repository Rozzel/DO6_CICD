_add-sanitize:
	$(eval FLAGS += -fsanitize=address -fsanitize=undefined -g -O0)

debugging: clean _add-sanitize unittests _unittests-forking_disable _test-compile
