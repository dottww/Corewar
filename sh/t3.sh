#!/bin/sh

for ((i=1; i<=$2; i++));
do
	echo "cycle =$i"
	./corewar -dump $i $1 $2 $3 > zzmine
	./corewar42 -v 31 -d $i $1 $2 $3> zzofi
	result=`diff zmine zofi -s`
	if [ "${result}" != "Files zzmine and zzofi are identical" ];then
		echo "Dump diff at=$i"
		break
	fi
done

diff zzmine zzofi -s

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