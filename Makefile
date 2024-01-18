target:
	gcc -g main.c -o main

ck:
	valgrind --leak-check=full ./main
	
clean:
	rm -rf main