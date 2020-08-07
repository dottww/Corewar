# #!/bin/sh
# make
# 	./corewar $1 $2 $
# 	./corewar42 $i $1 $2 $3 $4 > zzofi.txt
# 	result=`diff zzmine.txt zzofi.txt -s`
# 	if [ "${result}" != "Files zzmine.txt and zzofi.txt are identical" ];then
# 		echo "Dump diff at cycle= $i"
# 		break
# 	fi
# done

# diff zzmine.txt zzofi.txt -s > zzdiff.txt
./asm42 $1
./asm42 $2
./asm42 $3
./asm42 $4

echo ""${1%.s}.cor" "${2%.s}.cor" "${3%.s}.cor" "${4%.s}.cor""

echo "1=\""${1%.s}.cor"\" ; 2=\""${2%.s}.cor"\" ; 3=\""${3%.s}.cor"\" ; 4=\""${4%.s}.cor"\""
# echo 2=\""${2%.s}.cor"\"
echo 3=\""${3%.s}.cor"\"
echo 4=\""${4%.s}.cor"\" 
# echo "./corewar42 -d $i $1 $2 $3 $4"



		# open -a Visual\ Studio\ Code zzmine.txt
		# open -a Visual\ Studio\ Code zzofi.txt
		# open -a Visual\ Studio\ Code zzdiff.txt
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