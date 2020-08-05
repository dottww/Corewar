#!/bin/sh
make

PAUL=zzpaul.txt
MINE=zzmine.txt
OFI=zzofi.txt
DIFF=zzdiff.txt

echo "verbose compare :"
echo "./cc -v 31 ${1} > ${MINE}"
echo "./corewar${1} > ${OFI}"

	./cc -v 31 $1  > ${PAUL}
	./corewar $1 > ${MINE}
	./corewar42 -v 31 $1 > ${OFI}

diff "${MINE}" "${OFI}" -s > "$DIFF"


		# open -a Visual\ Studio\ Code ${MINE}
		# open -a Visual\ Studio\ Code ${OFI}
		open -a Visual\ Studio\ Code ${DIFF}
		# open -a Visual\ Studio\ Code ${PAUL}


echo "./corewar $1"
echo "./corewar42 -v 31 $1"