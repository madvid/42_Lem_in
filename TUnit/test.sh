## 1st argument corresponds to the number of tests to do
## 2nd argument corresponds to the type of test you want the generator to do
## To read the generator manual: type `./generator --help`

POWDER_BLUE=$(tput setaf 153)
WHITE=$(tput setaf 7)
BRIGHT=$(tput bold)
NORMAL=$(tput sgr0)
UNDERLINE=$(tput smul)
RED=$(tput setaf 1)

if [ "$1" != "" ] && [ "$2" != "" ] && [ -f "generator" ] && [ -f "lem-in" ] ; then
	total=$1
	for ((i=1; i<=$total; i++))
	do
		./generator $2 > test.txt
		sleep 1
		rounds=`./lem-in < test.txt --solution | wc -l`
		expected=`tail -n 1 test.txt | grep -Eo "\d+"`
		deviation=$((rounds-expected))
		echo "scale=2; $deviation*100/$expected" | bc > percentage.txt
		percentage=`cat percentage.txt`
		printf 'Test #%-5d: Expected: %5d | Output: %5d  (diff: %5.2f%%)\n'\
		$i $expected $rounds $percentage
		sum=$((sum+deviation))
		sump=$sump+$percentage
		total1=$((total1+expected))
		total2=$((total2+rounds))
	done

	if [[ $((sum/total)) < 2 ]] ; then
		c=''
	else
		c='s'
	fi
	echo "-------------------------------------------------------------"
	deviation=$((total2-total1))
	echo "scale=2; $deviation*100/$total1" | bc > percentage.txt
	percentage=`cat percentage.txt`
	printf "${BRIGHT}${WHITE}TOTAL      : Expected: %5d | Output: %5d  (diff: %5.2f%%)${NORMAL}"\
	$total1 $total2 $percentage
	echo "\n\n${WHITE}${BRIGHT}Standard deviation: $((sum/total)) round$c${NORMAL}"
	rm test.txt
	rm percentage.txt
fi
