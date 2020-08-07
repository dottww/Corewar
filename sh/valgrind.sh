COR=`ls champs/examples/*.cor | shuf -n $1 | tr '\n' ' '`

MINE="mine.info"

VALGRIND="valgrind.info"

OFI="ofi.info"

echo ".cor = ${COR}"
echo "valgrind --leak-check=full --track-origins=yes --show-leak-kinds=all --show-reachable=yes ./corewar ${COR}2> ${VALGRIND} > ${MINE}"
echo "./42corewar_linux ${COR}> ${OFI}"

valgrind --leak-check=full --track-origins=yes --show-leak-kinds=all --show-reachable=yes ./corewar ${COR} 2> ${VALGRIND} > ${MINE}

./42corewar_linux ${COR}> ${OFI}

compare=`diff ${MINE} ${OFI} -s`
if [ "${compare}" != "Files ${MINE} and ${OFI} are identical" ];then
	echo "\n>>>>>>>>>>>>>>>>>winner diff .cor =  ${COR}<<<<<<<<<<<<<<<<<<<<<<<<\n"
else
	echo "\n${compare}\n"
	echo `grep 'ERROR SUMMARY' ${VALGRIND}`
fi