#!/bin/sh
make

PAUL=zzpaul.txt
MINE=zzmine.txt
OFI=zzofi.txt
DIFF=zzdiff.txt
PAULDIFF=zzpauldiff.txt

echo "verbose compare :"
echo "./cc -v 31 -dump 10010 ${1} $2 > ${PAUL}"
echo "./corewar -dump 10010 ${1} $2 > ${MINE}"
echo "./corewar42 -v 31 ${1} $2 -d 10010 > ${OFI}"
echo "diff ${MINE} ${OFI} -s > $DIFF"

	# ./cc -v 31 -dump 25905 $1 $2 > ${PAUL}
	./corewar -dump 100100 $1 $2 > ${MINE}
	./corewar42 -v 31 $1 $2 -d 100100 > ${OFI}
	# ./corewar42  $1 $2 -d 25905 > ${OFI}

diff "${MINE}" "${OFI}" -s > "$DIFF"
# diff "${PAUL}" "${OFI}" -s > "$PAULDIFF"


# 		open -a Visual\ Studio\ Code ${MINE}
# 		open -a Visual\ Studio\ Code ${OFI}
# 		open -a Visual\ Studio\ Code ${DIFF}
		# open -a Visual\ Studio\ Code ${PAUL}
		# open -a Visual\ Studio\ Code ${PAULDIFF}
