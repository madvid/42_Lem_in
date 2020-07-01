BLACK=$(tput setaf 0)
RED=$(tput setaf 1)
GREEN=$(tput setaf 2)
YELLOW=$(tput setaf 3)
LIME_YELLOW=$(tput setaf 190)
POWDER_BLUE=$(tput setaf 153)
BLUE=$(tput setaf 4)
MAGENTA=$(tput setaf 5)
CYAN=$(tput setaf 6)
WHITE=$(tput setaf 7)
BRIGHT=$(tput bold)
NORMAL=$(tput sgr0)
BLINK=$(tput blink)
REVERSE=$(tput smso)
UNDERLINE=$(tput smul)

if [ "$1" != "" ] && [ -f "generator" ] && [ -f "lem-in" ] && [ "$2" == "" ] ; then
	printf "${UNDERLINE}${BRIGHT}${WHITE}Launching $1 tests for all categories of the generator\n\n"
	printf "${UNDERLINE}${BRIGHT}${POWDER_BLUE}1) flow-one: generates an ant farm with distinctive path and [1] ant in it${NORMAL}\n"
	./test.sh $1 --flow-one

	printf "\n${UNDERLINE}${BRIGHT}${POWDER_BLUE}2) flow-ten: generates an ant farm with distinctive paths and approximately [10] ants in it ${NORMAL}\n"
	./test.sh $1 --flow-ten

	printf "\n${UNDERLINE}${BRIGHT}${POWDER_BLUE}3) flow-thousand : generates an ant farm with distinctive path and approximately [100] ants in it${NORMAL}\n"
	./test.sh $1 --flow-thousand

	printf "\n${UNDERLINE}${BRIGHT}${POWDER_BLUE}4) big: generates a big map (approximately [1000] rooms) to test the time complexity${NORMAL}\n"
	./test.sh $1 --big

	printf "\n${UNDERLINE}${BRIGHT}${POWDER_BLUE}5) big-superposition : generates a big map with overlapping paths${NORMAL}\n"
	./test.sh $1 --big-superposition
elif [ "$1" != "" ] && [ -f "generator" ] && [ -f "generator" ] && [ -f "lem-in" ] && [ "$2" != "" ] ; then
	./test.sh $1 $2
fi
