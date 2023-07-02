#!/bin/bash

ERROR=-1
SUCCESS=0
TRUE=1
FALSE=0
IS_VALGRIND_INSTALLED=$FALSE
IS_MEM_LEAKS=$FALSE
BASEDIR=$(dirname "$0")

source $BASEDIR/integration_test.sh
source $BASEDIR/unit_test.sh
source $BASEDIR/valgrind.sh

case $1 in
	integration_test)
		integration_test ;;
	unit_test)
		unit_test ;;
	memory)
		check_leaks ;;
	*)
		printf "Invalid Arg (or missing)" ;;
esac
