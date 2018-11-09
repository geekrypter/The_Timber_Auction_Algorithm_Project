compile1:
	g++ timber_auction_dp.cpp -o timber_auction_dp
compile2:
	g++ timber_auction_bruteforce.cpp -o timber_auction_bruteforce
run1:
	./timber_auction_dp $(input_file)
run2:
	./timber_auction_bruteforce $(input_file)