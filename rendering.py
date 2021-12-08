import numpy as np
import pygame
import sys


class Board:
    def __init__(self):
        self.board = np.zeros((3, 3), dtype=np.int8)

    def __getitem__(self, item):
        return self.board[item]

    def __setitem__(self, key, value):
        self.board[key] = value

    def __repr__(self):
        return str(self.board)


class Rendering:
    def __init__(self):
        pygame.init()
        self.size = 120, 120
        self.grid = 3
        self.margin = self.size[0] / 3
        self.screen = pygame.display.set_mode(self.size)
        self.cross = pygame.image.load("cross.png")
        self.cross = pygame.transform.scale(self.cross, (20, 20))
        self.circle = pygame.image.load("circle.png")
        self.circle = pygame.transform.scale(self.circle, (20, 20))
        self.board = Board()
        self.board[1, 1] = 1
        self.board[1, 2] = 2
        self.board_list = []
        print(self.board)

    def draw(self):
        while True:
            for event in pygame.event.get():
                if event.type == pygame.QUIT:
                    sys.exit()
            self.screen.fill("0x272822")
            self.draw_board()
            self.draw_pieces()
            pygame.display.update()

    def draw_board(self):
        for i in range(self.grid):
            for j in range(self.grid):
                self.board_list.append(
                    pygame.draw.rect(
                        self.screen, "0xF8F8F2", (i * 30, j * 30, 30, 30), 0
                    )
                )
        pygame.draw.line(self.screen, "0xE69F66", (0, 30), (90, 30))
        pygame.draw.line(self.screen, "0xE69F66", (0, 60), (90, 60))
        pygame.draw.line(self.screen, "0xE69F66", (30, 0), (30, 90))
        pygame.draw.line(self.screen, "0xE69F66", (60, 0), (60, 90))

    def draw_pieces(self):
        for i in range(3):
            for j in range(3):
                if self.board[i, j] == 1:
                    self.screen.blit(self.circle, self.board_list[i * 3 + j])
                elif self.board[i, j] == 2:
                    self.screen.blit(self.cross, self.board_list[i * 3 + j])


if __name__ == "__main__":
    rendering = Rendering()
    rendering.draw()
