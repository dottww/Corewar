	./corewar $1 > mine
	./old $1 > ofi
	diff mine ofi > dif