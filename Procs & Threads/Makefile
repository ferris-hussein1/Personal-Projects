all:
	@echo "Compilation error: Choose 'proc' or 'thread'"

proc: searchtest.c multitest_proc.o
	gcc -c multitest_proc.c
	gcc searchtest.c multitest_proc.o -o searchtest -lm

thread: searchtest.c multitest_thread.o
	gcc -c multitest_thread.c
	gcc searchtest.c multitest_thread.o -o searchtest -lpthread -lm

clean:
	rm searchtest
	rm *.o