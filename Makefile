all : main

main : main.o

clean :
	-rm -f main *.o
