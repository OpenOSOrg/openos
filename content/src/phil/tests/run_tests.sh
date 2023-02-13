#!/bin/bash
TIMEOUT_SECONDS=5

all_tests=( "$@" )
test_count=$#
fail_count=0

for test_file in "${all_tests[@]}"
do
	printf "\033[1;39m===== %s =====\033[0m\n" "${test_file}"
	timeout ${TIMEOUT_SECONDS} "${test_file}"
	rc=$?
	if [ ${rc} -eq 0 ]
	then
		printf "\033[1;32mPASS\033[0m\n"
	elif [ ${rc} -eq 124 ]
	then
		printf "\033[1;31mFAIL (%d second timeout)\033[0m\n" "${TIMEOUT_SECONDS}"
		fail_count=$((fail_count + 1))
	else
		printf "\033[1;31mFAIL (rc = %d)\033[0m\n" "${rc}"
		fail_count=$((fail_count + 1))
	fi
done

printf "\n%d out of %d tests failed.\n" "${fail_count}" "${test_count}"
