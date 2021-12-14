import numpy as np


class Game:
    def __init__(self):
        self.state = np.zeros((3, 3), dtype=np.ushort)

    def new_game(self):
        self.state = np.zeros((3, 3), dtype=np.ushort)

    def step(self, player, x, y):
        self.state[x, y] = player

    def judge_end(self):
        return False

    @property
    def currentMove(self):
        s = np.sum(self.state == 0) % 2
        if s == 0:
            return 2
        return 1
