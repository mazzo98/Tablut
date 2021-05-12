all: Bitboard.o ListMoves.o Board.o main clean
	
Bitboard.o: Bitboard.c
	gcc -c -fPIC Bitboard.c
	gcc -shared Bitboard.o -o _bitboard.so

ListMoves.o: ListMoves.c
	gcc -c -fPIC ListMoves.c
	gcc -shared ListMoves.o -o _listMoves.so
	
Board.o: Board.c
	gcc -c -fPIC Board.c
	gcc -shared Board.o -o _board.so ListMoves.o Bitboard.o
	
main: Bitboard.o Board.o ListMoves.o main.c
	gcc -c -fPIC main.c
	gcc -o main main.o Bitboard.o ListMoves.o Board.o

clean:
	rm *.o