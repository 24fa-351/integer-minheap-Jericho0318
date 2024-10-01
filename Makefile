asst6: asst6.c some_heap.c
	gcc -o asst6 asst6.c some_heap.c -lm

clean:
	rm asst6
	rm some_heap