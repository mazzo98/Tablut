import math
import numpy as np
import time
import multiprocessing
import collections

from tablut.rules.ashton import Board, Player
from copy import deepcopy

BOARD_SIDE = 9
BOARD_SIZE = BOARD_SIDE * BOARD_SIDE

def flatten_move(start: tuple, end: tuple) -> int:
    flattened_start = (start[0] * BOARD_SIDE) + start[1]
    flattened_end = (end[0] * BOARD_SIDE) + end[1]
    return ((flattened_start * BOARD_SIZE) + flattened_end)


def deflatten_move(move: int) -> tuple:
    """
    Received moves in in [0, 64**2].
    To get the starting flattened we divide by 64, for the ending flattened we 
    take the modulo of 64.

    To get the single coords of a move we take division and modulo by 8
    """
    start, end = divmod(move, BOARD_SIZE)
    start = divmod(start, BOARD_SIDE)
    end = divmod(end, BOARD_SIDE)
    return start, end


class SearchWorker (multiprocessing.Process):
    def __init__(self, root_state, max_time, queue, max_depth, number):
        multiprocessing.Process.__init__(self)
        self._root_state = root_state
        self._max_time = max_time
        self._needed_moves = list()
        self._max_depth = max_depth
        self._queue = queue
        self._number = number
    
    def run(self):
        start_t = time.time()
        self.simulations = 0

        while ((time.time() - start_t)) <= self._max_time:
            # select leaf
            leaf = self._root_state.select_leaf()
            # obtain a new leaf
            leaf = leaf.expand()
            # save the number of moves needed to reach this leaf
            used_moves = self._max_depth - leaf.remaining_moves
            self._needed_moves.append(used_moves)
            # propagate leaf result
            leaf.backup()

            # the number of simulations carried out
            self.simulations += 1

        print("MCTS %d performed %d simulations" % (self._number, self.simulations))

        # search for best move
        for move, node in self._root_state.children.items():
            print("Move %s -> %s, %s/%s" %
                  (*deflatten_move(move), node.total_value, node.number_visits))

        move, node = max(self._root_state.children.items(),
                         key=lambda item: (item[1].total_value / item[1].number_visits))

        values = dict([(m, c.total_value / c.number_visits) for (m, c) in self._root_state.children.items()])

        self._queue.put(values)

    def get_result(self):
        return self._queue.get()

class Node(object):
    """
    Based on https://www.moderndescartes.com/essays/deep_dive_mcts/
    """

    def __init__(self, game, playing_as, parent=None, move=None, remaining_moves=50, C=np.sqrt(2)):
        self.game = game
        self.playing_as = playing_as
        self.move = move

        self.remaining_moves = remaining_moves
        self.C = C

        self.parent = parent
        self.children = {}  # Dict[move, Node instance]

        # search legal moves starting from the current state
        self.legal_moves = [
            flatten_move(*x) for x in self.possible_moves()
            if game.board.is_legal(game.turn, *x)[0]]
        self._number_visits = 0

        # if no moves can be performed the current player loses!
        if len(self.legal_moves) == 0:
            self.game.ended = True
            self._number_visits = self._number_visits + 1
            self.total_value = 0 if game.turn is Player.WHITE else 1
        else:
            self.child_total_value = np.zeros(
                [len(self.legal_moves)], dtype=np.float32)
            self.child_number_visits = np.zeros(
                [len(self.legal_moves)], dtype=np.float32)

    def _possible_starting_positions(self):
        """
        Compute the possible starting positions for the current player
        """
        if self.game.turn is Player.WHITE:
            positions = (self.game.board.board == 2) | (
                self.game.board.board == 1) | (self.game.board.board == 1.7)
        else:
            positions = (self.game.board.board == -2.5) | (
                self.game.board.board == -2)
        return np.transpose(np.where(positions))

    def _possible_ending_positions(self):
        """
        Compute the possible starting positions for the current player
        """
        positions = self.game.board.board == 0
        if self.game.turn is Player.WHITE:
            positions = positions | (self.game.board.board == 0.7) | (
                self.game.board.board == 0.3)
        else:
            positions = positions | (self.game.board.board == -0.5)
        return np.transpose(np.where(positions))

    def _is_orthogonal(self, start, end):
        """
        Check if the move is orthogonal
        """
        return start[0] == end[0] or start[1] == end[1]

    def possible_moves(self):
        """
        Computes all the possible moves given the current game state
        """
        starts = [tuple(x) for x in self._possible_starting_positions()]
        ends = [tuple(x) for x in self._possible_ending_positions()]

        moves = [(s, e)
                 for s in starts for e in ends if self._is_orthogonal(s, e)]
        return moves

    @property
    def number_visits(self):
        """
        Number of times a child has been visited (reduce its U)
        """
        idx = self.parent.legal_moves.index(self.move)
        return self.parent.child_number_visits[idx]

    @number_visits.setter
    def number_visits(self, value):
        idx = self.parent.legal_moves.index(self.move)
        self.parent.child_number_visits[idx] = value

    @property
    def total_value(self):
        """
        How many win has been totalized passing through that node
        """
        idx = self.parent.legal_moves.index(self.move)
        return self.parent.child_total_value[idx]

    @total_value.setter
    def total_value(self, value):
        idx = self.parent.legal_moves.index(self.move)
        self.parent.child_total_value[idx] = value

    def child_Q(self):
        """
        Calculate Q of each child as the number of wins of that child divided by the number of plays of
        that child if we select him
        e.g. already know quality of the node, how good we know that child is 
        """
        return self.child_total_value / (1 + self.child_number_visits)

    def child_U(self):
        """
        Calculate U of each child as sqrt(2) * sqrt(ln(N) / n) where N is the number of visits of
        this node, and n is the number of visits of the child if we choose him 
        U is unexpectancy e.g. how little we have explored that child 
        """
        u = self.C * (np.sqrt(np.log(self.number_visits + 2) /
                              (1 + self.child_number_visits)))
        return u

    def best_child(self):
        """
        Return the most promising move among childs
        """
        idx = np.argmax(self.child_Q() + self.child_U())
        return self.legal_moves[idx]

    def select_leaf(self):
        """
        Traverse tree reaching a leaf node who hasn't been expanded
        yet, choose the best child based on the evaluations made on them
        """
        # a leaf is considered so until it has some unused child
        # we go down further until our children list is not empty
        current = self
        while current.children:
            best_move = current.best_child()
            current = current.maybe_add_child(best_move)
        return current

    def expand(self):
        """
        Expand the game by taking random actions until a win condition is met
        """
        current = self
        rng = np.random.default_rng()
        while not current.game.ended and current.remaining_moves > 0:
            move = rng.choice(current.legal_moves)
            current = current.maybe_add_child(move)
        return current

    def add_child(self, move):
        """
        Add a child node
        """
        new_game = deepcopy(self.game)
        # skip legality check when making move as we only try legal moves
        if new_game.turn is Player.WHITE:
            new_game.white_move(*deflatten_move(move), known_legal=True)
        else:
            new_game.black_move(*deflatten_move(move), known_legal=True)

        rm = self.remaining_moves - 1
        self.children[move] = Node(
            new_game, self.playing_as, parent=self, move=move, remaining_moves=rm, C=self.C)
        return self.children[move]

    def maybe_add_child(self, move):
        """
        If a move have already been performed in the past return its associated child,
        otherwise create it
        """
        if move not in self.children:
            self.add_child(move)
        return self.children[move]

    def backup(self):
        """
        Backpropagate results.
        Note that depending on the player who is making the move whe need to change the 
        value estimation sign so that each player can take the best possible actions.
        In this scenario as WHITE moves first we invert when BLACK is playing.
        """
        ended = self.game.ended
        won = self.game.winner is self.playing_as
        current = self
        while current.parent is not None:
            current.number_visits += 1

            if ended and won:
                current.total_value += (1 + (self.remaining_moves * (10**-2)))

            current = current.parent


class Root(Node):
    def __init__(self, game, playing_as, C=None, **kwargs):
        self._number_visits = 0
        self._total_value = 0
        super().__init__(game, playing_as, C=C, parent=None, move=None, **kwargs)

    @property
    def number_visits(self):
        """
        Number of times this node has been visited
        """
        return self._number_visits

    @number_visits.setter
    def number_visits(self, value):
        """
        Sets the times this node has been visited
        """
        self._number_visits = value

    @property
    def total_value(self):
        """
        How many wins passing through this node has been totalized
        """
        return self._total_value

    @total_value.setter
    def total_value(self, value):
        """
        Set how many wins passing through this node has been totalized
        """
        self._total_value = value


class MCTS(object):
    """
    Perform montecarlo tree search on the tablut game.
    """

    def __init__(self, game_state, playing_as, max_depth=20, C=np.sqrt(2), parallel=multiprocessing.cpu_count()):
        self.max_depth = max_depth
        self.parallel_count = parallel
        self._root = Root(game_state, playing_as,
                          remaining_moves=max_depth, C=C)

    def search(self, max_time):
        """
        Perform search using a specified amount of simulations
        Max time represents the number of secs before timeout
        """
        workers = []
    
        #We use root parallelization approach where each workers create and explore its own tree.
        #At the end we merge resulting trees and we select best move from it
        for i in range(self.parallel_count):
            w = SearchWorker(deepcopy(self._root), max_time, multiprocessing.Queue(), self.max_depth, i)
            print("Workers %s" % i)
            workers.append(w)
        
        for w in workers:
            w.start()
         
        results = []
        for w in workers:
            results.append(w.get_result())
            w.join()

        values = collections.defaultdict(float)  
        for r in results:
            for (move, value) in r.items():
                values[move] += value
        
        move = max(values.items(), key=lambda item: item[1])[0]
       
        return deflatten_move(move)