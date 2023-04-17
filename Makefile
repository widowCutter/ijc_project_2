foo= htab_bucket_count.c htab_clear.c htab_erase.c htab_find.c htab_for_each.c htab_free.c htab_hash_function.c htab_init.c htab_lookup_add.c htab_size.c htab_statistics.c

run: wordcount-s wordcount-d
	./wordcount-s < ./words.txt
	LD_LIBRARY_PATH="." ./wordcount-dynamic < ./words.txt
	./wordcount- < ./words.txt
	
tailrun: tail
	./tail -n 10 < ./test.txt > stdin.txt
	./tail -n 10 test.txt > c_tail.txt
	tail -n 10 test.txt  > n_tail.txt
	cmp -s c_tail.txt n_tail.txt
	cmp -s stdin.txt n_tail.txt
	
tail: tail.c
	gcc -g -std=c11 -pedantic -Wall -Wextra -fsanitize=address tail.c -o tail
	
wordcount-s: libhtab.a
	$(CC) $(CFLAGS) wordcount.c -o wordcount-s -static libhtab.a -L.
	
wordcount-d: libhtab.so
	$(CC) $(CFLAGS) -g wordcount.c -o wordcount-dynamic libhtab.so -L.
libhtab.a: libhtab.o
	ar -crs libhtab.a htab_*.o
	ranlib libhtab.a
	
libhtab.so: libhtab.o 
	$(CC) $(CFLAGS) -shared -o libhtab.so htab_*.o

libhtab.o: htab_*.c
	$(CC) -c $(foo)

clean:
	rm *.o
	rm wordcount-s
