run: tail
	./tail
	./tail -n 30
tail: tail.c
	gcc -g -std=c11 -pedantic -Wall -Wextra -fsanitize=address tail.c -o tail
