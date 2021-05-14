all: Bitboard.o ListMoves.o Board.o clean
	
Bitboard.o: Bitboard.c
	gcc -c -O3 -fPIC Bitboard.c

ListMoves.o: ListMoves.c
	gcc -c -O3 -fPIC ListMoves.c
	
Board.o: Board.c
	gcc -c -O3 -fPIC Board.c
	gcc -shared Board.o -o _board.so ListMoves.o Bitboard.o

clean:
	rm *.o