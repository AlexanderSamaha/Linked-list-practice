list: main.o list.o
	gcc -g -o list main.o list.o
list.o: list.c
	gcc -g -c list.c
main.o: main.c
	gcc -g -c main.c
clean:
	rm -r *.o
	rm list

