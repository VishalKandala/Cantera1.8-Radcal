#!/bin/sh

# test target -> make the program and run the test
test:
	./runtest /usr/bin/python2
	@cd tut1; ./runtest /usr/bin/python2
	@cd tut2; ./runtest /usr/bin/python2
	@cd tut3; ./runtest /usr/bin/python2
	@cd tut4; ./runtest /usr/bin/python2
	@cd flame1; ./runtest /usr/bin/python2

# clean target -> clean up
clean:
	../../bin/rm_cvsignore
	cd tut1; ./cleanup
	cd tut2; ./cleanup
	cd tut3; ./cleanup
	cd tut4; ./cleanup
	cd flame1; ./cleanup

depends:

