

out : quicksorted.o print.o
	cc -o a.out quicksorted.o print.o

quicksorted.o: quicksorted.c
	cc -c quicksorted.c

print.o : print.c
	cc -c print.c

clean :
	rm a.out quicksorted.o print.o
