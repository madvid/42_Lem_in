#!/bin/sh

if [ -f colors.sh ]; then
	. colors.sh
fi

MAP_PATH=../maps/valid
INPUT_DATA=data_valid.txt
VALGRIND=""

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
	printf "\n"
	if [ -f "${MAP_PATH}/${map}" ];then
		bash checker.sh ${LEM_IN_EXEC} ${MAP_PATH}/${map} ${VALGRIND}
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
	printf "%s\n" "Usage: ./check_valid.sh exec"
	printf "%s\n" "Or Usage: ./check_valid.sh -v exec"
	printf "%s\n" "  -exec   Path to executable, -v with valgrind"
	exit
}

if [ $# -ne 1 ] && [ $# -ne 2 ] ;then
	print_usage_and_exit
	exit
fi

if [ $# -eq 2 ] && [ "$1" == "-v" ];then
	LEM_IN_EXEC=$2
	VALGRIND="valgrind"
else
	LEM_IN_EXEC=$1
fi

if [ ! -f ${LEM_IN_EXEC} ];then
	printf "%s\n" "Executable (${LEM_IN_EXEC}) not found"
	exit
fi

run_all_tests

