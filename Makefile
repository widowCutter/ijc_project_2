run: tail
	./tail < ./test.txt
tail: tail.c
	gcc -g -std=c11 -pedantic -Wall -Wextra -fsanitize=address tail.c -o tail
