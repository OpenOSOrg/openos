#!/bin/bash
TIMEOUT_SECONDS=5

all_tests=$@
test_count=$#
fail_count=0

for test_file in $all_tests
do
	echo "===== ${test_file} ====="
	rm -f testfs # Tidy up from previous tests
	timeout ${TIMEOUT_SECONDS} ${test_file}
	rc=$?
	if [ ${rc} -eq 0 ]
	then
		echo "PASS"
	elif [ ${rc} -eq 124 ]
	then
		echo "FAIL (${TIMEOUT_SECONDS} second timeout)"
		fail_count=$((fail_count + 1))
	else
		echo "FAIL (rc = ${rc})"
		fail_count=$((fail_count + 1))
	fi
done

echo "${fail_count} out of ${test_count} tests failed."
