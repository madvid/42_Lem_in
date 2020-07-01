#!/bin/sh

if [ -f colors.sh ]; then
	. colors.sh
fi

MAP_PATH=../maps/invalid
INPUT_DATA=check_invalid.txt

TEST_TMP=test_temp

print_ok()
{
	printf "${GREEN}%s${RESET}" "$1"
}

print_error()
{
	printf "${RED}%s${RESET}" "$1"
}

print_warning()
{
	printf "${YELLOW}%s${RESET}" "$1"
}

run_test()
{
	local name=`echo $@ | cut -d';' -f1`
	local map=`echo $@ | cut -d';' -f2`

	printf "%-50s" "$map"
	if [ -f "${MAP_PATH}/${map}" ];then
		if [ "$VALGRIND" -eq 1 ];then
			printf "with valgrind :      "
			valgrind -q --leak-check=full --track-origins=yes --show-leak-kinds=all --show-reachable=yes --suppressions=false_pos_valgrind.supp ${LEM_IN_EXEC} < "${MAP_PATH}/${map}" > /dev/null 2> ${TEST_TMP}
			# valgrind -q --leak-check=full --error-exitcode=42 --suppressions=false_pos_valgrind.supp ${LEM_IN_EXEC} < "${MAP_PATH}/${map}" > /dev/null 2> ${TEST_TMP}
		else
			${LEM_IN_EXEC} < "${MAP_PATH}/${map}" > /dev/null 2> ${TEST_TMP}
		fi
		local output=`cat -e ${TEST_TMP}`
		if [ ${output} = "ERROR" ]; then
		# if [ "${output:0:5}" = "ERROR" ]; then
			print_ok "Good!"
		else
			print_error "Booo!"
		fi
		printf "%5s%-60s" "" "`cat -e ${TEST_TMP}`"
	else
		print_warning "File not found"
	fi
	printf "\n"
}

run_all_tests()
{
	while read line
	do
		run_test ${line}
	done < ${INPUT_DATA}
}

print_usage_and_exit()
{
	printf "%s\n" "Usage: ./check_invalid.sh exec"
	printf "%s\n" "Or Usage: ./check_invalid.sh -v exec"
	printf "%s\n" "  -exec   Path to executable"
	exit
}

if [ $# -ne 1 ] && [ $# -ne 2 ] ;then
	print_usage_and_exit
	exit
fi


if [ $# -eq 2 ] && [ "$1" == "-v" ];then
	LEM_IN_EXEC=$2
	VALGRIND=1
else
	LEM_IN_EXEC=$1
	VALGRIND=0
fi

if [ ! -f $LEM_IN_EXEC ];then
	printf "%s\n" "Executable ($LEM_IN_EXEC) not found"
	exit
fi

run_all_tests

rm $TEST_TMP
