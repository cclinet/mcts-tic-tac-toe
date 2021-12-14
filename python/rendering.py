import math

import pygame

from Game import Game
from mcts import run_mcts


class UserInterface:
    def __init__(self):
        pygame.init()
        self.window = pygame.display.set_mode((1100, 580))  # 设置游戏窗口大小
        pygame.display.set_caption("Tic-tac-toe")  # 设置游戏窗口名称

        self.running = True  # 运行状态
        self.clock = pygame.time.Clock()  # 帧数控制

        self.game = Game()

        # 选中对象
        self.pick_player1 = None
        self.pick_player2 = None
        self.isCheat = False
        self.human_pick = None

        # 颜色类
        self.GrassGreen = (226, 240, 217)  # 草绿
        self.DarkKhaki = (189, 183, 107)  # 深卡其布
        self.LightBlue = (0, 176, 240)  # 浅蓝
        self.Pink = (235, 179, 235)  # 粉红
        self.Black = (59, 56, 56)  # 黑色
        self.Red = (255, 104, 76)  # 胡萝卜红

        # 常用属性类
        self.BGCOLOR = self.GrassGreen  # 背景色
        self.INTERVAL = 0.5  # 行动间隔
        self.FPS = 40  # 帧数
        self.SIZE_L = 150  # 游戏内常用尺寸(地图块 物品块等)
        self.SIZE_M = 80
        self.SIZE_S = 25

        # 字体类
        self.font = pygame.font.Font("texture/arialbd.ttf", self.SIZE_S)
        self.font1 = pygame.font.Font("texture/BD_Cartoon_Shout.ttf", 20)
        self.font2 = pygame.font.Font("texture/arialbd.ttf", 20)

        # 图片类
        self.img_circle = pygame.image.load(
            "texture/circle.png"
        ).convert_alpha()  # convert_alpha() 加载图片去黑边
        self.img_circle = pygame.transform.smoothscale(
            self.img_circle, (self.SIZE_M, self.SIZE_M)
        )
        self.img_cross = pygame.image.load("texture/cross.png").convert_alpha()
        self.img_cross = pygame.transform.smoothscale(
            self.img_cross, (self.SIZE_M, self.SIZE_M)
        )
        self.img_pick = pygame.image.load("texture/pick.png").convert_alpha()
        self.img_pick = pygame.transform.smoothscale(self.img_pick, (35, 35))

        # 文字类
        self.player1_text = self.font1.render(
            "PLAYER1", True, self.LightBlue
        )  # True: 抗锯齿
        self.player2_text = self.font1.render("PLAYER2", True, self.Pink)
        self.Q_text = self.font.render("Q", True, self.Black)
        self.random_text = self.font.render("random", True, self.Black)
        self.human_text = self.font.render("human", True, self.Black)
        self.start_text = self.font1.render("START", True, self.Red)
        self.cheat_text = self.font.render("CHEAT", True, self.Black)

    # 开始一局游戏
    def start_game(self):
        self.game.new_game()

    # 玩家1行动
    def player1_move(self):
        pos = run_mcts(self.game.state.flatten())
        x, y = divmod(pos, 3)
        # x, y = self.human_pick
        if self.game.state[x][y] == 0:
            self.game.step(1, x, y)
            self.human_pick = None

    # 玩家2行动
    def player2_move(self):
        x, y = self.human_pick
        if self.game.state[x][y] == 0:
            self.game.step(2, x, y)
            self.human_pick = None

    # 玩家输入
    def process_input(self):
        for event in pygame.event.get():
            # 按下右上角的游戏退出键
            if event.type == pygame.QUIT:
                self.running = False
                break
            elif event.type == pygame.MOUSEBUTTONDOWN:  # 按下鼠标
                x, y = pygame.mouse.get_pos()
                if event.button == 1:  # 按下鼠标左键
                    print(x, " ", y)
                    # 是否作弊
                    # if 600 <= x <= 675 and 180 <= y <= 200:
                    #     temp = self.isCheat
                    #     self.isCheat = True if temp is False else False
                    # 选择player1
                    # if 740 <= x <= 760 and 55 <= y <= 70:
                    #     self.pick_player1 = "Q"
                    # elif 800 <= x <= 890 and 55 <= y <= 70:
                    #     self.pick_player1 = "random"
                    # elif 940 <= x <= 1020 and 55 <= y <= 70:
                    #     self.pick_player1 = "human"
                    # 选择player2
                    # if 740 <= x <= 760 and 105 <= y <= 120:
                    #     self.pick_player2 = "Q"
                    # elif 800 <= x <= 890 and 105 <= y <= 120:
                    #     self.pick_player2 = "random"
                    # 开始游戏
                    if 940 <= x <= 1025 and 105 <= y <= 120:
                        self.start_game()
                        self.human_pick = None
                    # 选择井字格
                    if 50 <= x <= 500 and 50 <= y <= 500:
                        row = math.floor((x - 50) / self.SIZE_L)
                        col = math.floor((y - 50) / self.SIZE_L)
                        self.human_pick = (row, col)
                        print(self.human_pick)

    # 更新界面状态
    def update(self):
        if self.game.judge_end():
            self.human_pick = None
        elif self.human_pick is not None:
            if self.game.currentMove == 1:
                self.player1_move()
            elif self.game.currentMove == 2:
                self.player2_move()
            self.human_pick = None

    # 更新显示
    def render(self):
        # 填充背景色
        self.window.fill(self.BGCOLOR)

        # 显示分隔线
        for i in range(4):
            pygame.draw.line(
                self.window,
                self.DarkKhaki,
                (50, 50 + i * self.SIZE_L),
                (50 + 3 * self.SIZE_L, 50 + i * self.SIZE_L),
                8,
            )
            pygame.draw.line(
                self.window,
                self.DarkKhaki,
                (50 + i * self.SIZE_L, 50 + 3 * self.SIZE_L),
                (50 + i * self.SIZE_L, 50),
                8,
            )

        # 显示图片
        for i, row in enumerate(self.game.state):
            for j, one in enumerate(row):
                if one == 1:
                    self.window.blit(
                        self.img_cross, (85 + i * self.SIZE_L, 85 + j * self.SIZE_L)
                    )
                if one == 2:
                    self.window.blit(
                        self.img_circle, (85 + i * self.SIZE_L, 85 + j * self.SIZE_L)
                    )

        # 显示信息面板
        # player1
        self.window.blit(self.player1_text, (600, 55))
        self.window.blit(self.Q_text, (740, 50))
        self.window.blit(self.random_text, (800, 50))
        self.window.blit(self.human_text, (940, 50))
        if self.pick_player1 == "Q":
            self.window.blit(self.img_pick, (740, 60))
        elif self.pick_player1 == "random":
            self.window.blit(self.img_pick, (800, 60))
        elif self.pick_player1 == "human":
            self.window.blit(self.img_pick, (940, 60))
        # player2
        self.window.blit(self.player2_text, (600, 105))
        self.window.blit(self.Q_text, (740, 100))
        self.window.blit(self.random_text, (800, 100))
        self.window.blit(self.start_text, (940, 105))
        if self.pick_player2 == "Q":
            self.window.blit(self.img_pick, (740, 110))
        elif self.pick_player2 == "random":
            self.window.blit(self.img_pick, (800, 110))

        # 显示作弊
        self.window.blit(self.cheat_text, (600, 180))
        # if self.isCheat:
        #     self.window.blit(self.img_pick, (600, 190))
        #     for i in range(4):
        #         pygame.draw.line(
        #             self.window,
        #             self.Black,
        #             (740, 180 + i * self.SIZE_M),
        #             (740 + 3 * self.SIZE_M, 180 + i * self.SIZE_M),
        #             2,
        #         )
        #         pygame.draw.line(
        #             self.window,
        #             self.Black,
        #             (740 + i * self.SIZE_M, 180 + 3 * self.SIZE_M),
        #             (740 + i * self.SIZE_M, 180),
        #             2,
        #         )
        #     if self.game.currentMove == "blue":
        #         try:
        #             Q_Sa = self.agent.Q_table[str(self.game.state)]
        #             for action in Q_Sa:
        #                 i, j = str2tuple(action)
        #                 value = round(Q_Sa[action], 3)
        #                 text = self.font2.render(str(value), True, self.Black)
        #                 self.window.blit(
        #                     text, (750 + i * self.SIZE_M, 205 + j * self.SIZE_M)
        #                 )
        #         except:
        #             pass

        # pygame刷新显示
        pygame.display.update()

        # 主循环

    def run(self):
        while self.running:
            self.process_input()
            self.update()
            self.render()
            self.clock.tick(self.FPS)


if __name__ == "__main__":
    render = UserInterface()
    render.run()
