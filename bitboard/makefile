all: Bitboard.o Board.o main clean
	
Bitboard.o: Bitboard.c
	gcc -c Bitboard.c
	
Board.o: Board.c
	gcc -c Board.c
	
main: Bitboard.o Board.o main.c
	gcc -c main.c
	gcc -o main main.o Bitboard.o Board.o
clean:
	rm *.o
