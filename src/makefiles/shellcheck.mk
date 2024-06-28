test-shellcheck: _dir-report
	find . -name "*.sh" -exec shellcheck {} + > report/shellcheck.txt
