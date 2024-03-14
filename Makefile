target:
	gcc -g stack-queue.c -o main

ck:
	valgrind --leak-check=full ./main
	
clean:
	rm -rf main