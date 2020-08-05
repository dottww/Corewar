#!/bin/sh
make

MINE=zzmine.txt
OFI=zzofi.txt
DIFF=zzdiff.txt

echo "verbose compare :"
echo "./corewar ${1} > ${MINE}"
echo "./corewar42 -v 31 ${1} > ${OFI}"

	./corewar -dump 15  $1 > ${MINE}
	./corewar42 -v 31 $1 -d 15 > ${OFI}

diff "${MINE}" "${OFI}" -s > "$DIFF"


		open -a Visual\ Studio\ Code ${MINE}
		open -a Visual\ Studio\ Code ${OFI}
		# open -a Visual\ Studio\ Code "$DIFF"


echo "./corewar $1"
echo "./corewar42 -v 31 $1"