run: wordcount
	./wordcount- < ./tailtest/test.txt
	
tailrun: tail
	./tail -n 10 < ./test.txt > stdin.txt
	./tail -n 10 test.txt > c_tail.txt
	tail -n 10 test.txt  > n_tail.txt
	cmp -s c_tail.txt n_tail.txt
	cmp -s stdin.txt n_tail.txt
	
tail: tail.c
	gcc -g -std=c11 -pedantic -Wall -Wextra -fsanitize=address tail.c -o tail
	
wordcount: wordcount-.cc
	g++ -O2 wordcount-.cc -o wordcount-
