#!/bin/sh
make

./asm $1
./asm $2
./asm $3
./asm $4

MINE=zzmine.txt
OFI=zzofi.txt
DIFF=zzdiff.txt

./corewar "${1%.s}.cor" "${2%.s}.cor" "${3%.s}.cor" "${4%.s}.cor"| tail > ${MINE}
./corewar_linux "${1%.s}.cor" "${2%.s}.cor" "${3%.s}.cor" "${4%.s}.cor"| tail > ${OFI}

diff "${MINE}" "${OFI}" -s > "$DIFF"

result=`diff "${MINE}" "${OFI}" -s`
if [ "${result}" != "Files ${MINE} and ${OFI} are identical" ];then
printf "Diff\n"
else
printf "Same\n"
fi

echo mine:
cat zzmine.txt
echo ofi:
cat zzofi.txt
echo diff:
cat zzdiff.txt