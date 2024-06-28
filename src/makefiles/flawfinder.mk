_flawfinder: _dir-report
	flawfinder --minlevel=0 --columns --context --html . > report/flawfinder.html

test-flawfinder: _flawfinder
