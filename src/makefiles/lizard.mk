_lizard: _dir-report
	lizard --html . -x "./artifacts/*" > report/lizard.html

test-lizard: _lizard
