CHECK_INCLUDES=tests_check/includes.check
CHECK_FILES=$(filter-out $(CHECK_INCLUDES), $(wildcard tests_check/*.check))

_unittests.check: $(CHECK_INCLUDES) $(CHECK_FILES)
	$(MAKE) test-check_numbering
	cat $^ > tests_check/$@

_unittests-forking_disable: unittests
ifeq ($(UNAME_S),Linux)
	sed -i 's/srunner_run_all/srunner_set_fork_status(sr, CK_NOFORK);\n\n  srunner_run_all/' $^.c
endif

test-check_numbering:
	@for file in $$(find tests_check -name "*.check"); do \
		cp $$file $$file.bak; \
		awk -v count=1 -v prev="" ' \
		/^#test/ { \
			split($$0, a, " "); \
			gsub(/[0-9]+$$/, "", a[2]); \
			if(a[2] != prev){ \
				count = 1; \
				prev = a[2]; \
			} \
			printf "%s %s%d", a[1], a[2], count++; \
			for (i=3; i<=length(a); i++) printf " %s", a[i]; \
			print ""; \
		} \
		!/^#test/ {print $$0}' $$file.bak > $$file; \
		rm $$file.bak; \
	done

unittests: _unittests.check
	rm -f tests_check/$@
	checkmk clean_mode=1 tests_check/$^ > $@.c
	rm -f tests_check/$^
	clang-format -style=$(CODE_STYLE) -i $@.c
