"""Main module"""
import tkinter as tk
import time
from math import sin, cos, radians
from threading import Thread
import random as rnd

def close():
    """Closes the window"""
    win.destroy()

WIN_H = 700
WIN_W = 1200

CENTER_X = WIN_W/2
CENTER_Y = WIN_H/2
win = tk.Tk()
win.title("Animation")
win.config(width=WIN_W, height=WIN_H)
win.resizable(False, False)
win.protocol("WM_DELETE_WINDOW", close)

cnv = tk.Canvas(win, bg="#036", highlightthickness=0)
cnv.place(x=0, y=0, width=WIN_W, height=WIN_H)

class Planet():
    """Class of planet"""
    def __init__(self, speed, x_coord, y_coord ,radius, canvas, distance, color):
        """Initialization of planet"""
        self.x_coord = x_coord
        self.y_coord = y_coord
        self.speed = speed
        self.dist = distance
        self.angle = 0
        self.canvas = canvas
        self.planet = canvas.create_oval(x_coord - radius, y_coord - radius,
                                         x_coord + radius, y_coord + radius,
                                         fill=color)

    def move(self):
        """Function that moves planet in canvas"""
        while True:
            self.angle = (self.angle + self.speed) % 360
            self.x_coord = CENTER_X + self.dist * cos(radians(self.angle))
            self.y_coord = CENTER_Y + self.dist * sin(radians(self.angle))
            self.canvas.coords(self.planet, self.x_coord - 10,
                               self.y_coord - 10, self.x_coord + 10,
                               self.y_coord + 10)
            self.canvas.update()
            time.sleep(0.01)
R = 20
sun = cnv.create_oval(CENTER_X - R, CENTER_Y - R, CENTER_X + R,
                          CENTER_Y + R, fill="yellow", outline="red",
                            width=3)

colors = ["orange", "white", "green", "red", "yellow", "cyan", "blue"]
pls = []
for i in range(8):
    pl = Planet(rnd.randint(1, 6), 50*(i+1), CENTER_Y, rnd.randint(8, 25),
                 cnv, 70 + 50*(i + 1), colors[rnd.randint(0, 6)])
    pls.append(pl)
for pl in pls:
    t = Thread(target=pl.move, daemon=True)
    t.start()

win.mainloop()
