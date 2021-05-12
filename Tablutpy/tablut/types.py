from ctypes import *

class Bitboard(Structure):
    _fields_ = [("bb", c_uint32 * 3)]

class Board(Structure):
    _fields_ = [ ("black", Bitboard), 
                 ("white", Bitboard), 
                 ("king", Bitboard)]

class Position(Structure):
    _fields_ = [("row", c_uint8), 
                ("col", c_uint8) ]

class Move(Structure):
    _fields_ = [("start", Position), 
                ("end", Position) ]