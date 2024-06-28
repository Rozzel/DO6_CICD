_cformat_n:
	$(call run_cformat,-n)

_cformat_i:
	$(call run_cformat,-i)

test-style: _cformat_n _cformat_i

test-style_ci:
	find . \( \( -name "*.c" -o -name "*.h" \) \) -print0 | xargs -0 -n 1 clang-format -style=$(CODE_STYLE) --Werror -n --verbose

define run_cformat
	find . -type f \( -name "*.c" -o -name "*.h" \) -exec clang-format -style=$(CODE_STYLE) $(1) {} \;
endef
