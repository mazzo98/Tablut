from enum import Enum
from copy import deepcopy
from tablut.board import WinException, DrawException, LoseException


class Player(Enum):
    WHITE = "W"
    BLACK = "B"

    def next(self):
        if self is self.WHITE:
            return self.BLACK
        else:
            return self.WHITE


class TurnException(Exception):
    pass


class Game(object):
    """
    Create a tablut board and lets the user play
    """

    def __init__(self, board):
        self.board = board
        self.turn = Player.WHITE
        self.end = False

    @property
    def ended(self):
        return self.board.winning_condition() or self.board.lose_condition() or self.board.draw_condition() or self.end

    @property
    def winner(self):
        if self.board.winning_condition():
            return Player.WHITE
        elif self.board.lose_condition():
            return Player.BLACK
        else:
            return None

    def white_move(self, start, end):
        """
        Make the white move
        """
        if self.turn == Player.WHITE and not self.ended:
            try:
                self.board.step(start, end)
                self.turn = Player.BLACK
            except WinException:
                # white won
                pass
            except LoseException:
                # white lost (shouldn't happen after a white move right now)
                # FIXME: Stuck player?
                pass
            except DrawException:
                pass
            except Exception as e:
                raise ValueError("White move illegal: %s" % str(e))
        else:
            raise TurnException("Its black player turn")

    def black_move(self, start, end):
        """
        Make the black move
        """
        if self.turn == Player.BLACK:
            try:
                self.board.step(start, end)
                self.turn = Player.WHITE
            except WinException:
                # white won (shouldn't happen here...)
                # FIXME: Implement stuck player?
                pass
            except LoseException:
                # white lost
                pass
            except DrawException:
                pass
            except Exception as e:
                raise ValueError("Black move illegal:%s " % str(e))
        else:
            raise TurnException("Its white player turn")
