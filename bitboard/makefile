all: Bitboard.o List.o Board.o main clean
	
Bitboard.o: Bitboard.c
	gcc -c Bitboard.c
		
List.o: List.c
	gcc -c List.c
	
Board.o: Board.c
	gcc -c Board.c
	
main: Bitboard.o List.o Board.o main.c
	gcc -c main.c
	gcc -o main main.o Bitboard.o List.o Board.o

clean:
	rm *.o
