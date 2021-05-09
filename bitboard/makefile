all: Bitboard.o List.o Board.o main clean
	
Bitboard.o: Bitboard.c
	gcc -c Bitboard.c
	gcc -shared Bitboard.o -o _bitboard.so
		
List.o: List.c
	gcc -c List.c
	gcc -shared List.o -o _list.so
	
Board.o: Board.c
	gcc -c Board.c
	gcc -shared Board.o -o _board.so
	
main: Bitboard.o List.o Board.o main.c
	gcc -c main.c
	gcc -o main main.o Bitboard.o List.o Board.o

clean:
	rm *.o
