#!/bin/bash

integration_run_tester()
{
	local exec_name=$1

	set_is_valgrind_installed
	if [ $IS_VALGRIND_INSTALLED -eq $TRUE ]; then
		integration_run_with_valgrind $exec_name
	else
		$ROOT_DIR/$exec_name >> $ROOT_DIR/$INT_TEST_RES
	fi
}

integration_test()
{
	# run test and save in INT_TEST_RES
	rm $INT_TEST_RES
	rm int_leaks.txt

	for EXEC in $INT_TEST_EXEC
	do
		integration_run_tester $EXEC
	done

	if [ $IS_VALGRIND_INSTALLED -eq $TRUE ]; then
		cat *.valgrind_out.intergration.test.txt >> int_leaks.txt
		rm *.valgrind_out.intergration.test.txt
		cat int_leaks.txt >> $ROOT_DIR/$VALGRIND_OUTPUT
	fi

	# print res
	cat $ROOT_DIR/$INT_TEST_RES

	# check for failed tests
	STT=$( cat $ROOT_DIR/$INT_TEST_RES | grep -a "FAILED TEST" | awk '{print $1}')

	# # return the status as true/false
	if [[ $STT -eq 0 ]]
	then
		return $SUCCESS
	else
		return $ERROR
	fi
}

