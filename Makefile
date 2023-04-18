foo= htab_bucket_count.c htab_clear.c htab_erase.c htab_find.c htab_for_each.c htab_free.c htab_hash_function.c htab_init.c htab_lookup_add.c htab_size.c htab_statistics.c
build: tail wordcount-s wordcount-d
	

run: wordcount-s wordcount-d tail
	./wordcount < ./stdin.txt
	LD_LIBRARY_PATH="." ./wordcount-dynamic < ./stdin.txt
	# ./tail -n 10 
	
tail: tail.c
	gcc -g -std=c11 -pedantic -Wall -Wextra tail.c -o tail
	
wordcount-s: libhtab-s
	$(CC) $(CFLAGS) wordcount.c -o wordcount -static libhtab.a -L.
	
wordcount-d: libhtab-d
	$(CC) $(CFLAGS) -g wordcount.c -o wordcount-dynamic libhtab.so -L.
	
libhtab-s: libhtab-o
	ar -crs libhtab.a htab_*.o
	
libhtab-d: libhtab-o 
	$(CC) $(CFLAGS) -shared -o libhtab.so htab_*.o

libhtab-o: htab_*.c
	$(CC) -c htab_*.c -fPIC

clean:
	rm *.o libhtab.a libhtab.so
	rm wordcount wordcount-dynamic tail
