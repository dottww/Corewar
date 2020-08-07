#!/bin/sh

make

PAUL=zzpaul1.txt
MINE=zzmine1.txt
OFI=zzofi1.txt
DIFF=zzdiff1.txt
PAULDIFF=zzpauldiff1.txt

echo "verbose compare :"
echo "./cc -v 31 -dump $i $1 $2 $3 > ${PAUL}"
echo "./corewar -dump $i $1 $2 $3 > ${MINE}"
echo "./corewar42 -v 31 $1 $2 $3 -d $i > ${OFI}"
echo "diff ${MINE} ${OFI} -s > $DIFF"

for ((i=$5; i<=$5; i++));
do
	echo "cycle =$i"
	./corewar -dump $i $1 $2 $3> ${MINE}
	./corewar42 -v 31 -d $i $1 $2 $3 > ${OFI}
	result=`diff ${MINE} ${OFI} -s`
	if [ "${result}" != "Files ${MINE} and ${OFI} are identical" ];then
		echo "\n>>>>>>>>>>>>>>>>>Dump diff at = $i<<<<<<<<<<<<<<<<<<<<<<<<\n"
		break
	fi
done

diff ${MINE} ${OFI} -s > "$DIFF"



# ./corewar -n 2 p1.cor -n 1 zork.cor


# test() {./asm42 $1 && make && ./corewar "${1%.s}.cor" ;}

# ./corewar seg.cor

# ./asm $1
# cp "${1%.s}.cor" "zmine.cor"
# ./42asm_mac $1
# cp "${1%.s}.cor" "zofi.cor"
# hexdump -vC zmine.cor > zmine
# hexdump -vC zofi.cor > zofi
# diff zmine zofi -s