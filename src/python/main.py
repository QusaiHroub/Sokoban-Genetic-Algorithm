import tkinter
import numpy as np
import sokoban_boost
import time

class SokobanGui:
    def __init__(self, multiplier=75):
        self.colors = {
            " ": {"fill": '#ded7b3', "stroke": '#ded7b3'},
            "#": {"fill": '#868687', "stroke": '#505051'},
            "$": {"fill": '#d9ae0a', "stroke": '#C79300'},
            "*": {"fill": '#4ccd5a', "stroke": '#3ca448'},
            ".": {"fill": '#dfbbb1', "stroke": '#ca8e7d'},
            "?": {"fill": '#4f99e8', "stroke": '#3f7ab9'},
        }

        self.top = tkinter.Tk()
        self.canvas = tkinter.Canvas(self.top, bg="blue", height=700, width=700)
        self.multiplier = multiplier

    def render(self, sokoban, options=None):
        if options and options.restart:
            return

        for line in range(0, 7):
            for cell in range(0, 6):
                self.paintCell(sokoban.get_at(line, cell), line, cell)

        self.canvas.pack()
        self.top.update()

    def circle(self, x, y, r, width, color='black'):
        self.canvas.create_oval(x + r, y + r, x - r, y - r, width=width, fill=color,)

    def paintCell(self, cell, x, y):
        if cell == '.' or cell == '?':
            circle_size = 10
            if cell == '?':
                circle_size = 20

            rect_x = x * self.multiplier
            rect_y = y * self.multiplier
            self.canvas.create_rectangle(rect_x, rect_y, rect_x + self.multiplier, rect_y + self.multiplier,
                                         fill=self.colors.get(" ").get("fill"),
                                         outline=self.colors.get(" ").get("fill"))

            arc_x = rect_x + 75 / 2
            arc_y = rect_y + 75 / 2
            self.circle(arc_x, arc_y, circle_size, 0, self.colors.get(cell).get("fill"))

        else:
            rect_x = x * self.multiplier
            rect_y = y * self.multiplier
            self.canvas.create_rectangle(rect_x, rect_y, rect_x + self.multiplier, rect_y + self.multiplier,
                                         fill=self.colors.get(cell).get("stroke"),
                                         outline=self.colors.get(cell).get("fill"))
            self.canvas.create_rectangle(rect_x + 5, rect_y + 5, rect_x + self.multiplier - 10, rect_y + self.multiplier - 10,
                                         fill=self.colors.get(cell).get("fill"),
                                         outline=self.colors.get(cell).get("fill"))


gui = SokobanGui()
sokoban = sokoban_boost.Sokoban()
while not sokoban.is_end():
    sokoban.move()
    gui.render(sokoban)
    time.sleep(.5)


print('done...')
