#!/bin/bash

integration_run_with_valgrind()
{
	local exec_name=$1
	local base="$(basename $exec_name)"
	local name=${base%.*}
	local out_file="$name.valgrind_out.intergration.test.txt"
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --log-file=$out_file $exec_name >> $ROOT_DIR/$INT_TEST_RES
}

run_with_valgrind()
{
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --log-file=$VALGRIND_OUTPUT $ROOT_DIR/$TEST_EXEC > $ROOT_DIR/$UNIT_TEST_RES
}

check_leaks()
{
	set_is_valgrind_installed
	if [ $IS_VALGRIND_INSTALLED -eq $TRUE ]; then
		# local STT_INT=$(grep "ERROR SUMMARY:" int_leaks.txt | awk '{print $4}')

		local STT=$(grep "ERROR SUMMARY:" $VALGRIND_OUTPUT | awk '{print $4}')

		if [ "$STT" == "0" ]; then
			printf "No Leaks :)"
			return $SUCCESS
		else
			cat $VALGRIND_OUTPUT
			return $ERROR
		fi
	else
		printf "valgrind is not installed"
	fi
}

set_is_valgrind_installed()
{
	local OUT_PUT=$(command -v valgrind)
	if [ "$OUT_PUT" == "" ] ; then
		IS_VALGRIND_INSTALLED=$FALSE
	else
		IS_VALGRIND_INSTALLED=$TRUE
	fi
}

