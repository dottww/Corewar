#!/bin/sh
make

MINE=zzmine.txt
OFI=zzofi.txt
DIFF=zzdiff.txt

for ((i=$2; i<=$3; i++));
do
	# echo "cycle =$i"
	./corewar -dump $i $1 > ${MINE}
	./corewar42 -v 31 -d $i $1 > ${OFI}
	result=`diff "${MINE}" "${OFI}" -s`
	if [ "${result}" != "Files ${MINE} and ${OFI} are identical" ];then
		echo "Dump diff at cycle= $i"
		diff "${MINE}" "${OFI}" -s > "$DIFF"
		open -a Visual\ Studio\ Code "$DIFF"
		break
	else
		echo "Same dump at cycle= $i"
		if [ $i == $3 ];then
		echo "All Same!!!"
		fi
	fi
done


./corewar "${1%.s}.cor" "${2%.s}.cor" "${3%.s}.cor" | tail > ${MINE}
./corewar42 "${1%.s}.cor" "${2%.s}.cor" "${3%.s}.cor" | tail > ${OFI}
# ./corewar_linux "${1%.s}.cor" "${2%.s}.cor" "${3%.s}.cor" | tail > ${OFI}


echo "./corewar -dump $i $1"
echo "./corewar42 -d $i $1"

	# ./corewar $i $1 $2 $3 $4  tail
	# ./corewar42 $i $1 $2 $3 $4  tail


		# open -a Visual\ Studio\ Code zzmine.txt
		# open -a Visual\ Studio\ Code zzofi.txt
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