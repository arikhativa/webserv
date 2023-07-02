#!/bin/bash

# run test and save in UNIT_TEST_RES
$ROOT_DIR/$TEST_EXEC > $ROOT_DIR/$UNIT_TEST_RES
# print res
cat $ROOT_DIR/$UNIT_TEST_RES
# check for failed tests
STT=$( cat $ROOT_DIR/$UNIT_TEST_RES | grep -a "asserts" | awk '{print $5}')
# return the status as true/false
if [[ $STT -eq 0 ]]
then
	true
else
	false
fi
